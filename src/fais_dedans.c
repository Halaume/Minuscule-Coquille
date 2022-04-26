/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:07:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/26 17:39:56 by tnaton           ###   ########.fr       */
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
	if (arg[1] && ft_strncmp(arg[1], "-n", ft_strlen(arg[1])) == 0)
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
		return (write(2, "cd: too many arguments\n", 24), 1);
	if (!arg[1])
	{
		home = get_my_home(envp);
		if (home == NULL)
			return (write(2, "bash: cd: HOME not set\n", 23), 1);
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
	{
		return (perror("erreur pwd wtf"), -1000);
	}
	else
		write(1, curdir, ft_strlen(curdir));
	return (0);
}

/*int	ft_exit(char **exit, t_info *info)
{
	if (exit[1])
	{
		info->exit_status = ft_atoi(exit[1]);
	}
	exit_func(status);
	return (0);
}*/

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
	while (commande[i] != '=')
		i++;
	if (strncmp(env_commande, commande, i) == 0)
		return (0);
	return (1);
}

int	ft_export(t_env *env, char **commande)
{
	t_env	*tmp;
	t_env	*new;
	int		i;

	tmp = env;
	new = NULL;
	while (tmp->next && !is_this_var(tmp->variable, commande[1]))
		tmp = tmp->next;
	new = malloc(sizeof(t_env));
	if (!new)
		return (perror("malloc issue"), -1);
	new->next = NULL;
	i = 0;
	if (is_this_var(tmp->variable, commande[1]))
	{
		while (commande[1][i])
		{
			if (commande[1][i] == '=')
			{
				tmp->variable = ft_substr(commande[1], 0, i);
				tmp->valeur = ft_substr(commande[1], i + 1, ft_strlen(commande[0]) - i);
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
			new->valeur = ft_substr(commande[1], i + 1, ft_strlen(commande[0]) - i);
			tmp->next = new;
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_env *env, char **commande)
{
	(void)env;
	(void)commande;

	return (0);
}

int	is_built_in(char *commande, t_info *info)
{
	char	**no_quote_commande;
	int		ret;
	int		i;

	if (!commande || !*commande)
		return (1);
	ret = 1;
	i = 1;
	no_quote_commande = NULL;
	no_quote_commande = ft_splitsane(commande);
	printf("%s\n", no_quote_commande[1]);
	if (!no_quote_commande)
		return (1);
	if (ft_strncmp("echo", no_quote_commande[0], 5) == 0)
		ret = ft_echo(no_quote_commande);
	else if (ft_strncmp("pwd", no_quote_commande[0], 4) == 0)
		ret = ft_pwd();
	else if (ft_strncmp("cd", no_quote_commande[0], 3) == 0)
		ret = ft_cd(no_quote_commande, info->envp);
	else if (ft_strncmp("export", no_quote_commande[0], 6) == 0)
		ret = ft_export(info->env, no_quote_commande);
	else if (ft_strncmp("unset", no_quote_commande[0], 5) == 0)
		ret = ft_unset(info->env, no_quote_commande);
	else if (ft_strncmp("env", no_quote_commande[0], 3) == 0)
		ret = ft_env(info->env);
//	else if (ft_strncmp("exit", no_quote_commande[0], 4) == 0)
//		ret = ft_exit(status);
	free_char_char(info->envp);
	info->envp = ft_getenvp(info->env);
	free_char_char(no_quote_commande);
	return (ret);
}

int	check_built_in(char *commande)
{
	char	**no_quote_commande;

	if (!commande || !*commande)
		return (1);
	no_quote_commande = NULL;
	no_quote_commande = ft_splitsane(commande);
	if (!no_quote_commande)
		return (1);
	if (ft_strncmp("echo", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
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
