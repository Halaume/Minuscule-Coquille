/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:07:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/26 11:03:00 by ghanquer         ###   ########.fr       */
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
		tmp = tmp->next;
	}
	return (0);
}

int	is_built_in(char *commande, t_info *info)
{
	char	**no_quote_commande;
	char	*joined_commande;
	int		ret;
	int		i;

	if (!commande || !*commande)
		return (1);
	ret = 1;
	i = 1;
	no_quote_commande = split_empty_line(commande, ' ');
	joined_commande = no_quote_commande[0];
	printf("no_quote_commande[0] = %s\n", no_quote_commande[0]);
	while (no_quote_commande[i])
	{
		printf("no_quote_commande[%d] = %s\n", i, no_quote_commande[i]);
		joined_commande = strjoin_space(joined_commande, no_quote_commande[i]);
//		printf("current join str %s\n", joined_commande);
		i++;
	}
	printf("final join str %s\n", joined_commande);
	free_char_char(no_quote_commande);
	no_quote_commande = NULL;
	no_quote_commande = no_quote_tab(joined_commande);
	if (!no_quote_commande)
		return (1);
	if (ft_strncmp("echo", no_quote_commande[0], 5) == 0)
		ret = ft_echo(no_quote_commande);
	else if (ft_strncmp("pwd", no_quote_commande[0], 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp("cd", no_quote_commande[0], 3) == 0)
		ret = ft_cd(no_quote_commande, info->envp);
//	else if (ft_strncmp("export", splitted_str[0], 6) == 0)
//		return (ft_export(splitted_str));
//	else if (ft_strncmp("unset", splitted_str[0], 5) == 0)
//		return (ft_unset(splitted_str));
	else if (ft_strncmp("env", no_quote_commande[0], 3) == 0)
		return (ft_env(info->env));
//	else if (ft_strncmp("exit", no_quote_commande[0], 4) == 0)
//		return (ft_exit(status));
	free(no_quote_commande);
	return (ret);
}

int	check_built_in(char *commande)
{
	char	**no_quote_commande;

	if (!commande || !*commande)
		return (1);
	no_quote_commande = NULL;
	no_quote_commande = ft_split(no_quote(commande), ' ');
	if (!no_quote_commande)
		return (1);
	if (ft_strncmp("echo", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (0);
	else if (ft_strncmp("pwd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (0);
	else if (ft_strncmp("cd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (0);
	else if (ft_strncmp("export", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (0);
	else if (ft_strncmp("unset", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (0);
	else if (ft_strncmp("env", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (0);
	else if (ft_strncmp("exit", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (0);
	free(no_quote_commande);
	return (1);
}
