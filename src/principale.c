/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:44:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/03 12:44:07 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

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
		if (ligne[i] == '"' && !simpleguillemet)
			doubleguillemet = !doubleguillemet;
		else if (ligne[i] == '\'' && !doubleguillemet)
			simpleguillemet = !simpleguillemet;
		else if (ligne[i] == '(' && !simpleguillemet && !doubleguillemet)
			parenthese++;
		else if (ligne[i] == ')' && !simpleguillemet && !doubleguillemet)
			parenthese--;
		if (parenthese < 0)
			return (1);
		i++;
	}
	if (parenthese != 0 || simpleguillemet != 0 || doubleguillemet != 0)
		return (1);
	return (0);
}

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

void	freearbre(t_arbre *arbre)
{
	char	*tmp;

	if (arbre->fd)
		freearbre(arbre->fd);
	if (arbre->fg)
		freearbre(arbre->fg);
	tmp = ft_strtrim(arbre->commande, "\"");
	if (!ft_strncmp(tmp, "/tmp/.", 6))
		unlink(tmp);
	free(tmp);
	free(arbre->commande);
	free(arbre);
}

int	checkarbre(t_arbre *arbre)
{
	char *tmp;

	if (arbre)
	{
		if (!ft_strcmp(arbre->commande, "()") || \
				!ft_strcmp(arbre->commande, "|") || \
				!ft_strcmp(arbre->commande, "&&") || \
				!ft_strcmp(arbre->commande, "||"))
		{
			if (arbre->fd)
			{
				tmp = ft_strtrim(arbre->fd->commande, " ");
				if (!ft_strcmp(tmp, "") || !ft_strcmp(tmp, ">") || \
						!ft_strcmp(tmp, ">>") || !ft_strcmp(tmp, "<") \
						|| !ft_strcmp(tmp, "<<"))
					return (free(tmp), 1);
				free(tmp);
			}
			if (arbre->fg)
			{
				tmp = ft_strtrim(arbre->fg->commande, " ");
				if (!ft_strcmp(tmp, "") || !ft_strcmp(tmp, ">") || \
						!ft_strcmp(tmp, ">>") || !ft_strcmp(tmp, "<") || \
						!ft_strcmp(tmp, "<<"))
					return (free(tmp), 1);
				free(tmp);
			}
			if ((!arbre->fg || !arbre->fd) && (!ft_strcmp(arbre->commande, "|")\
					   	|| !ft_strcmp(arbre->commande, "&&") \
						|| !ft_strcmp(arbre->commande, "||")))
				return (1);
			if (!arbre->fg && !arbre->fd)
				return (1);
		}
		else
		{
			tmp	= ft_strtrim(arbre->commande, " ");
			if (!ft_strcmp(tmp, ">") || !ft_strcmp(tmp, ">>") || \
					!ft_strcmp(tmp, "<") || !ft_strcmp(tmp, "<<"))
				return (free(tmp), 1);
			if (!ft_strncmp(tmp, "<<", 2))
			{
				free(arbre->commande);
				arbre->commande = open_heredoc(ft_substr(tmp, 2, ft_strlen(tmp) - 2));
			}
			free(tmp);
		}
		if (arbre->fd && arbre->fg)
			return (checkarbre(arbre->fd) + checkarbre(arbre->fg));
		else if (arbre->fg)
			return (checkarbre(arbre->fg));
		else if (arbre->fd)
			return (checkarbre(arbre->fd));
		tmp = ft_strtrim(arbre->commande, " ");
		if (!ft_strcmp(tmp, ""))
			return (free(tmp), 1);
		return (free(tmp), 0);
	}
	return (0);
}

t_env	*ft_getenv(char **envp)
{
	t_env	*first;
	t_env	*tmp;
	t_env	*current;
	int	i;
	int	j;
	
	first = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				tmp->variable = ft_substr(envp[i], 0, j);
				tmp->valeur = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j);
				if (i == 0)
				{ 
					current = tmp;
					first = current;
				}
				else
				{
					current->next = tmp;
					current = current->next;
					current->next = NULL;
				}
				break;
			}
			j++;
		}
		i++;
	}
	return (first);
}

void	freeenv(t_env *current)
{
	t_env	*tmp;

	while (current)
	{
		free(current->variable);
		free(current->valeur);
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

int	getsize(t_env *env)
{
	int i;
	
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

int	principale(int ac, char **av, char **envp)
{
	char	*ligne;
	t_info	info;
	char	*tmp;

	info.env = ft_getenv(envp);
	info.envp = ft_getenvp(info.env);
	info.exit_status = 0;
	ligne = readline("MinusculeCoquille$>");
	while (ligne)
	{
		tmp = ft_strtrim(ligne, " ");
		if (ft_strlen(tmp))
		{
			add_history(ligne);
			info.arbre = NULL;
			if (verifieligne(ligne))
			{
				printf("Erreur syntaxique\n");
				free(ligne);
			}
			else
			{
				info.arbre = analyse_syntaxique(ligne, info.arbre, &info);
				if (!checkarbre(info.arbre))
				{
				//	structure(info.arbre, 0);
					lance_exec(&info, info.arbre);
				}
				else
					printf("Erreur syntaxique\n");
			}
			if (info.arbre)
				freearbre(info.arbre);
		}
		else
			free(ligne);
		ligne = readline("MinusculeCoquille$>");
		free(tmp);
	}
	free(ligne);
	freeenv(info.env);
	free_char_char(info.envp);
	rl_clear_history();
	(void)ac;
	(void)av;
	(void)envp;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	return (principale(ac, av, envp));
}
