/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:07:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/24 15:21:01 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	is_built_in(char *str)
{
	char	**splitted_str;

	splitted_str = ft_split(str, ' ');
	if (ft_strncmp("echo", splitted_str[0], 4) == 0)
		return (ft_echo(splitted_str));
	else if (ft_strncmp("pwd", splitted_str[0], 3) == 0)
		return (ft_pwd(splitted_str));
	else if (ft_strncmp("cd", splitted_str[0], 2) == 0)
		return (ft_cd(splitted_str));
	else if (ft_strncmp("export", splitted_str[0], 6) == 0)
		return (ft_export(splitted_str));
	else if (ft_strncmp("unset", splitted_str[0], 5) == 0)
		return (ft_unset(splitted_str));
	else if (ft_strncmp("env", splitted_str[0], 3) == 0)
		return (ft_env(splitted_str));
	else if (ft_strncmp("exit", splitted_str[0], 4) == 0)
		return (ft_exit(splitted_str));
	return (0);
}
