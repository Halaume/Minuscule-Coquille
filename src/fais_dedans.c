/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:07:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/01 14:34:14 by ghanquer         ###   ########.fr       */
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
		while (arg[i] && ft_strncmp(arg[i], "-n", ft_strlen(arg[0])) == 0)
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

int	ft_cd(char **arg)
{
	if (arg[2])
		return (write(2, "cd: too many arguments\n", 24), 1);
	if (chdir(arg[1]) == -1)
		return (perror("cd"), 1);
	return (0);
}

int	is_built_in(char *commande)
{
	char	**no_quote_commande;
	int		ret;

	if (!commande || !*commande)
		return (1);
	ret = 1;
	no_quote_commande = NULL;
	no_quote_commande = ft_split(no_quote(commande), ' ');
	if (!no_quote_commande)
		return (1);
	if (ft_strncmp("echo", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_echo(no_quote_commande);
//	else if (ft_strncmp("pwd", splitted_str[0], 3) == 0)
//		return (ft_pwd(splitted_str));
	else if (ft_strncmp("cd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_cd(no_quote_commande);
//	else if (ft_strncmp("export", splitted_str[0], 6) == 0)
//		return (ft_export(splitted_str));
//	else if (ft_strncmp("unset", splitted_str[0], 5) == 0)
///		return (ft_unset(splitted_str));
//	else if (ft_strncmp("env", splitted_str[0], 3) == 0)
//		return (ft_env(splitted_str));
//	else if (ft_strncmp("exit", splitted_str[0], 4) == 0)
//		return (ft_exit(splitted_str));
	free(no_quote_commande);
	return (ret);
}

int	check_built_in(char *commande)
{
	char	**no_quote_commande;
	int		ret;

	if (!commande || !*commande)
		return (1);
	no_quote_commande = NULL;
	no_quote_commande = ft_split(no_quote(commande), ' ');
	if (!no_quote_commande)
		return (1);
	if (ft_strncmp("echo", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (0);
//	else if (ft_strncmp("pwd", splitted_str[0], 3) == 0)
//		return (ft_pwd(splitted_str));
	else if (ft_strncmp("cd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (0);
//	else if (ft_strncmp("export", splitted_str[0], 6) == 0)
//		return (0);
//	else if (ft_strncmp("unset", splitted_str[0], 5) == 0)
//		return (0);
//	else if (ft_strncmp("env", splitted_str[0], 3) == 0)
//		return (0);
//	else if (ft_strncmp("exit", splitted_str[0], 4) == 0)
//		return (0);
	free(no_quote_commande);
	return (1);
}
