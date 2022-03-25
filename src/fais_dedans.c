/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:07:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/25 16:00:16 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	ft_echo(t_arbre **arg)
{
	int	i;
	int	is_n_here;

	i = 0;
	is_n_here = 0;
	if (arg[0]->commande && ft_strncmp(arg[0]->commande, "-n", 3) == 0)
	{
		while (arg[i]->commande && ft_strncmp(arg[i]->commande, "-n", 3) == 0)
			i++;
		is_n_here = 1;
	}

	if (arg[i]->commande)
	{
		while (arg[i]->commande)
		{
			write(1, arg[i]->commande, ft_strlen(arg[i]->commande));
			i++;
		}
	}
	if (is_n_here == 0)
		write (1, "\n", 1);
	return (0);
}

int	ft_cd(t_arbre **arg)
{
	if (arg[1]->commande)
		return (write(2, "cd: too many arguments\n", 24), 1);
	if (chdir(arg[0]->commande) == -1)
		return (perror("cd"), 1);
	return (0);
}

int	is_built_in(t_arbre *commande)
{

	if (!commande->commande || !*commande->commande)
		return (-1);
	if (ft_strncmp("echo", commande->commande, 4) == 0)
		return (ft_echo(commande->argument));
//	else if (ft_strncmp("pwd", splitted_str[0], 3) == 0)
//		return (ft_pwd(splitted_str));
	else if (ft_strncmp("cd", commande->commande, 2) == 0)
		return (ft_cd(commande->argument));
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
