/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:07:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/25 10:50:51 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	ft_echo(char **splitted_str)
{
	int	i;
	int	is_n_here;

	i = 1;
	is_n_here = 0;
	if (splitted_str[1] && ft_strncmp(splitted_str[1], "-n", 3) == 0)
	{
		while (splitted_str[i] && ft_strncmp(splitted_str[i], "-n", 3) == 0)
			i++;
		is_n_here = 1;
	}

	if (splitted_str[i])
	{
		while (splitted_str[i])
		{
			write(1, splitted_str[i], ft_strlen(splitted_str[i]));
			i++;
		}
	}
	if (is_n_here == 0)
		write (1, "\n", 1);
	return (0);
}

int	ft_cd(char **splitted_str)
{
	if (splitted_str[2])
		return (write(2, "cd: too many arguments\n", 24), 1);
	if (chdir(splitted_str[2]) == -1)
		return (perror("cd"), 1);
	return (0);
}

int	is_built_in(char *str)
{
	char	**splitted_str;

	if (!str || !*str)
		return (-1);
	splitted_str = ft_split(str, ' ');
	if (ft_strncmp("echo", splitted_str[0], 4) == 0)
		return (ft_echo(splitted_str));
//	else if (ft_strncmp("pwd", splitted_str[0], 3) == 0)
//		return (ft_pwd(splitted_str));
	else if (ft_strncmp("cd", splitted_str[0], 2) == 0)
		return (ft_cd(splitted_str));
//	else if (ft_strncmp("export", splitted_str[0], 6) == 0)
//		return (ft_export(splitted_str));
//	else if (ft_strncmp("unset", splitted_str[0], 5) == 0)
///		return (ft_unset(splitted_str));
//	else if (ft_strncmp("env", splitted_str[0], 3) == 0)
//		return (ft_env(splitted_str));
//	else if (ft_strncmp("exit", splitted_str[0], 4) == 0)
//		return (ft_exit(splitted_str));
	return (1);
}
