/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:07:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/04 17:47:44 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	ft_echo(char **arg)
{
	int	i;
	int	is_n_here;
	int	first_word;

	first_word = 1;
	i = 1;
	is_n_here = 0;
	if (arg[1] && !ft_strcmp(arg[1], "") && !arg[2])
		return (write(1, "\n", 1), 0);
	if (arg[1] && ft_strcmp(arg[1], "-n") == 0)
	{
		while (arg[i] && ft_strncmp(arg[i], "-n", ft_strlen(arg[i])) == 0)
			i++;
		is_n_here = 1;
	}
	if (arg[i])
	{
		while (arg[i])
		{
			if (first_word == 0)
				write(1, " ", 1);
			write(1, arg[i], ft_strlen(arg[i]));
			if (first_word == 1)
				first_word = 0;
			i++;
		}
	}
	if (is_n_here == 0)
		write (1, "\n", 1);
	return (0);
}

char	*get_my_home(char **envp)
{
	int	i;

	i = 0;
	while (*envp && ft_strncmp("HOME=", *envp, 5) != 0)
	{
		i++;
		if (envp[i] == NULL)
			return (NULL);
	}
	if (!envp[i])
		return (NULL);
	return (envp[i + 5]);
}

int	ft_cd(char **arg, char **envp)
{
	char	*home;

	if (arg[2])
		return (write(2, "cd: arguments trop nombreux\n", 24), 1);
	if (!arg[1])
	{
		home = get_my_home(envp);
		if (home == NULL)
			return (write(2, "coquille: cd: HOME non set\n", 23), 1);
		else		
			if (chdir(home) == -1)
				return (perror("cd"), 1);
	}
	if (chdir(arg[1]) == -1)
		return (perror("cd"), 1);
	return (0);
}

int	ft_pwd(void)
{
	char	curdir[4096];

	if (getcwd(curdir, sizeof(curdir)) == NULL)
		return (perror("erreur pwd wtf"), -1000);
	else
	{
		write(1, curdir, ft_strlen(curdir));
		write(1, "\n", 1);
	}
	return (0);
}

int	is_exiting(char *numero)
{
	int	i;

	i = 0;
	if (numero[i] == '-' || numero[i] == '+')
		i++;
	while (numero[i])
	{
		if (!ft_isdigit(numero[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **exit, t_info *info)
{
	int	i;

	i = 0;
	if (exit[1])
	{
		while (exit[1][i])
		{
			if (is_exiting(exit[1]))
			{
				ft_putstr_fd("exit: Besoin argument numerique\n", 2);
				info->exit_status = 2;
				break ;
			}
			else
				info->exit_status = ft_atoi(exit[1]);
			i++;
		}
	}
	ft_putstr_fd("exit\n", 1);
	exit_func(info);
	return (0);
}

int	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd(tmp->variable, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(tmp->valeur, 1);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_this_var(char *env_commande, char *commande)
{
	int	i;

	i = 0;
	while (commande[i] && commande[i] != '=')
		i++;
	if (ft_strncmp(env_commande, commande, i) == 0)
		return (0);
	return (1);
}

int	check_identifier(char *commande)
{
	int	i;

	i = 0;
	if (ft_isdigit(commande[i]))
		return (0);
	while (commande[i])
	{
	if (commande[i] < '0' || (commande[i] > '9'  && commande[i] < 'A') || commande[i] >= 'z' || (commande[i] > 'Z' && commande[i] < '_') || commande[i] == '`')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_info *info, char **commande)
{
	t_env	*tmp;
	t_env	*new;
	int		i;

	i = 0;
	tmp = info->env;
	new = NULL;
	if (!check_identifier(commande[0]))
		return (ft_putstr_fd("export: identifier invalide\n", 2), 1);
	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("export malloc issue"), -1);
	new->next = NULL;
	if (!info->env)
	{
		while (commande[1][i])
		{
			if (commande[1][i] == '=')
			{
				new->variable = ft_substr(commande[1], 0, i);
				new->valeur = ft_substr(commande[1], i + 1, ft_strlen(commande[1]) - i);
				freeenv(info->env);
				info->env = new;
				return (0);
			}
			i++;
		}
	}
	while (tmp && tmp->next && is_this_var(tmp->variable, commande[1]))
		tmp = tmp->next;
	if (tmp && !is_this_var(tmp->variable, commande[1]))
	{
		while (commande[1][i])
		{
			if (commande[1][i] == '=')
			{
				tmp->variable = ft_substr(commande[1], 0, i);
				tmp->valeur = ft_substr(commande[1], i + 1, ft_strlen(commande[1]) - i);
				return (free(new), 0);
			}
			i++;
		}
	}
	while (commande[1][i])
	{
		if (commande[1][i] == '=')
		{
			new->variable = ft_substr(commande[1], 0, i);
			new->valeur = ft_substr(commande[1], i + 1, ft_strlen(commande[1]) - i);
			tmp->next = new;
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_info *info, char *commande)
{
	t_env	*tmp;
	t_env	*keep;

	tmp = info->env;
	if (!check_identifier(commande))
		return (ft_putstr_fd("unset: identifier invalide\n", 2), 1);
	while (tmp)
	{
		if (is_this_var(tmp->variable, commande) == 0)
		{
			if (tmp == info->env)
			{
				info->env = info->env->next;
				free(tmp->variable);
				free(tmp->valeur);
				tmp->variable = NULL;
				tmp->valeur = NULL;
				free(tmp);
			}
			else
			{
				keep->next = tmp->next;
				free(tmp->variable);
				free(tmp->valeur);
				tmp->variable = NULL;
				tmp->valeur = NULL;
				free(tmp);
			}
			return (0);
		}
		keep = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	is_built_in(char *commande, t_info *info)
{
	char	**no_quote_commande;
	int		ret;

	if (!commande || !*commande)
		return (1);
	ret = 1;
	no_quote_commande = NULL;
	no_quote_commande = ft_splitsane(commande, info);
	if (!no_quote_commande)
		return (1);
	if (ft_strlen(no_quote_commande[0]) == ft_strlen("echo") && ft_strncmp("echo", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_echo(no_quote_commande);
	else if (ft_strncmp("pwd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_pwd();
	else if (ft_strncmp("cd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_cd(no_quote_commande, info->envp);
	else if (ft_strncmp("export", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_export(info, no_quote_commande);
	else if (ft_strncmp("unset", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_unset(info, no_quote_commande[1]);
	else if (ft_strncmp("env", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_env(info->env);
	else if (ft_strncmp("exit", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_exit(no_quote_commande, info);
	free_char_char(info->envp);
	info->envp = ft_getenvp(info->env);
	free_char_char(no_quote_commande);
	return (ret);
}

int	check_built_in(char *commande, t_info *info)
{
	char	**no_quote_commande;

	if (!commande || !*commande)
		return (1);
	no_quote_commande = NULL;
	no_quote_commande = ft_splitsane(commande, info);
	if (!no_quote_commande)
		return (1);
	if (ft_strlen(no_quote_commande[0]) == ft_strlen("echo") && ft_strncmp("echo", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strncmp("pwd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strncmp("cd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strncmp("export", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strncmp("unset", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strncmp("env", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strncmp("exit", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	return (free_char_char(no_quote_commande), 1);
}
