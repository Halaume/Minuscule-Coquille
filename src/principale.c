/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:44:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/10 18:23:19 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	g_exit_status;

int	verifieligne(char *ligne)
{
	int	i;
	int	parenthese;
	int	doubleguillemet;
	int	simpleguillemet;

	parenthese = 0;
	i = 0;
	doubleguillemet = 0;
	simpleguillemet = 0;
	while (ligne[i])
	{
		gui(ligne[i], &doubleguillemet, &simpleguillemet, &parenthese);
		if (parenthese < 0)
			return (1);
		i++;
	}
	if (parenthese != 0 || simpleguillemet != 0 || doubleguillemet != 0)
		return (1);
	return (0);
}

/*
void	padding(char ch, int n)
{
	int	i;

	for (i = 0; i < n; i++)
		putchar(ch);
}

void	structure(t_arbre *root, int level)
{
	if (root == NULL)
		padding(' ', level);
	else
	{
		structure(root->fd, level + 1);
		padding('	', level);
		printf(">%s<\n", root->commande);
		structure (root->fg, level + 1);
	}
}
*/

void	freearbrecmd(t_arbre *arbre)
{
	char	*tmp;

	tmp = ft_strtrim(arbre->commande, "\"<");
	if (!ft_strncmp(tmp, "/tmp/.", 6))
		unlink(tmp);
	free(tmp);
	tmp = NULL;
	free(arbre->commande);
	arbre->commande = NULL;
}

void	freearbre(t_arbre *arbre)
{
	if (arbre)
	{
		if (arbre->fd)
		{
			freearbre(arbre->fd);
			arbre->fd = NULL;
		}
		if (arbre->fg)
		{
			freearbre(arbre->fg);
			arbre->fg = NULL;
		}
		if (arbre->commande)
			freearbrecmd(arbre);
		if (arbre)
		{
			free(arbre);
			arbre = NULL;
		}
	}
}

int	ischiant(t_arbre *arbre)
{
	return (!ft_strcmp(arbre->commande, "()") || \
			!ft_strcmp(arbre->commande, "|") \
		|| !ft_strcmp(arbre->commande, "&&") || \
		!ft_strcmp(arbre->commande, "||"));
}

int	istropchiant(char *tmp)
{
	return (!ft_strcmp(tmp, "") || !ft_strcmp(tmp, ">") || \
			!ft_strcmp(tmp, ">>") || !ft_strcmp(tmp, "<") || \
			!ft_strcmp(tmp, "<<"));
}

int	ft_ischiant(t_arbre *arbre, t_info *info)
{
	char	*tmp;

	if (info->arbre && arbre->fd)
	{
		tmp = ft_strtrim(arbre->fd->commande, " ");
		if (istropchiant(tmp))
			return (free(tmp), 1);
		free(tmp);
	}
	if (info->arbre && arbre->fg)
	{
		tmp = ft_strtrim(arbre->fg->commande, " ");
		if (istropchiant(tmp))
			return (free(tmp), 1);
		free(tmp);
	}
	if ((!arbre->fg || !arbre->fd) && (!ft_strcmp(arbre->commande, "|") \
			|| !ft_strcmp(arbre->commande, "&&") \
				|| !ft_strcmp(arbre->commande, "||")))
		return (1);
	if (!arbre->fg && !arbre->fd)
		return (1);
	return (0);
}

int	ft_istropchiant(t_arbre *arbre, t_info *info)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strtrim(arbre->commande, " ");
	if (istropchiant(tmp))
		return (free(tmp), 1);
	tmp2 = ft_strtrim(tmp, "\"");
	if (info->arbre && !ft_strncmp(tmp2, "<<", 2))
	{
		free(arbre->commande);
		if (info->arbre && asquote(tmp))
			arbre->commande = open_heredoc(ft_strdup(tmp), info);
		else if (info->arbre)
			arbre->commande = open_heredoc(ft_substr(tmp, 2, \
						ft_strlen(tmp) - 2), info);
	}
	free(tmp2);
	free(tmp);
	return (0);
}

int	casseburne(t_arbre *arbre)
{
	char	*tmp;

	tmp = ft_strtrim(arbre->commande, " ");
	if (!ft_strcmp(tmp, ""))
		return (free(tmp), 1);
	return (free(tmp), 0);
}

int	checkarbre(t_arbre *arbre, t_info *info)
{
	if (info->arbre && arbre)
	{
		if (ischiant(arbre))
		{
			if (ft_ischiant(arbre, info))
				return (1);
		}
		else if (info->arbre)
		{
			if (ft_istropchiant(arbre, info))
				return (1);
		}
		if (info->arbre && arbre->fd && arbre->fg)
			return (checkarbre(arbre->fd, info) + checkarbre(arbre->fg, info));
		else if (info->arbre && arbre->fg)
			return (checkarbre(arbre->fg, info));
		else if (info->arbre && arbre->fd)
			return (checkarbre(arbre->fd, info));
		if (info->arbre)
			return (casseburne(arbre));
	}
	return (0);
}

void	movea(t_getenv	*a)
{
	if (a->i == 0)
	{
		a->current = a->tmp;
		a->first = a->current;
	}
	else
	{
		a->current->next = a->tmp;
		a->current = a->current->next;
		a->current->next = NULL;
	}
}

t_env	*ft_getenv(char **envp)
{
	t_getenv	a;

	a.first = NULL;
	a.i = 0;
	while (envp[a.i])
	{
		a.tmp = (t_env *)malloc(sizeof(t_env));
		a.j = 0;
		while (envp[a.i][a.j])
		{
			if (envp[a.i][a.j] == '=')
			{
				a.tmp->variable = ft_substr(envp[a.i], 0, a.j);
				a.tmp->valeur = ft_substr(envp[a.i], a.j + 1, \
						ft_strlen(envp[a.i]) - a.j);
				movea(&a);
				break ;
			}
			a.j++;
		}
		a.i++;
	}
	return (a.first);
}

void	freeenv(t_env *current)
{
	t_env	*tmp;

	while (current)
	{
		free(current->variable);
		current->variable = NULL;
		free(current->valeur);
		current->valeur = NULL;
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

int	getsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**ft_getenvp(t_env *env)
{
	char	**envp;
	char	*tmp;
	int		i;

	i = 0;
	envp = (char **)malloc(sizeof(char *) * (getsize(env) + 1));
	while (env)
	{
		tmp = ft_strjoin(env->variable, "=");
		envp[i++] = ft_strjoin(tmp, env->valeur);
		free(tmp);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	singal(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	initinfo(t_info *info, char **envp)
{
	info->env = ft_getenv(envp);
	info->envp = ft_getenvp(info->env);
	info->arbre = NULL;
	info->isexport = 0;
	info->caner = 0;
	info->exit_status = 0;
	g_exit_status = 0;
	signal(SIGINT, &singal);
	signal(SIGQUIT, SIG_IGN);
}

void	freeprincip(t_info *info, char *ligne, int ac, char **av)
{
	ft_exit(NULL, info);
	free(ligne);
	freeenv(info->env);
	free_char_char(info->envp);
	rl_clear_history();
	(void)ac;
	(void)av;
}

void	lanceprin(char *ligne, t_info *info)
{
	add_history(ligne);
	info->arbre = NULL;
	if (verifieligne(ligne))
	{
		ft_putstr_fd("Erreur syntaxique\n", 2);
		free(ligne);
	}
	else
	{
		info->arbre = analyse_syntaxique(ligne, info->arbre, info);
		if (!checkarbre(info->arbre, info))
			lance_exec(info, info->arbre);
		else
			ft_putstr_fd("Erreur syntaxique\n", 2);
		info->caner = 0;
	}
	if (info->arbre)
	{
		freearbre(info->arbre);
		info->arbre = NULL;
	}
}

int	principale(int ac, char **av, char **envp)
{
	char	*ligne;
	t_info	info;
	char	*tmp;

	initinfo(&info, envp);
	ligne = readline("MinusculeCoquille$>");
	while (ligne)
	{
		if (g_exit_status)
			info.exit_status = g_exit_status;
		tmp = ft_strtrim(ligne, " ");
		if (ft_strlen(tmp))
			lanceprin(ligne, &info);
		else
			free(ligne);
		g_exit_status = 0;
		ligne = readline("MinusculeCoquille$>");
		free(tmp);
	}
	freeprincip(&info, ligne, ac, av);
	return (info.exit_status);
}

int	main(int ac, char **av, char **envp)
{
	return (principale(ac, av, envp));
}
