/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:21:15 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/11 12:21:30 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/MinusculeCoquille.h"

int	ft_cd(char **arg, t_info *info)
{
	char	*home;

	if (lencaca(arg) > 2)
		return (write(2, "cd: arguments trop nombreux\n", 28), 1);
	if (lencaca(arg) < 2)
	{
		home = get_my_home(info->env);
		if (home == NULL)
			return (write(2, "coquille: cd: HOME non set\n", 27), 1);
		else
		{
			if (chdir(home) == -1)
				return (perror("cd"), 1);
			else
				return (0);
		}
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

int	is_too_big(const char *nptr)
{
	int			i;
	long long	nbr;

	i = 0;
	nbr = 0;
	if (ft_strlen(nptr) > 20)
		return (0);
	while (nptr[i] == '\f' || nptr[i] == '\t' || nptr[i] == '\v'
		|| nptr[i] == '\n' || nptr[i] == '\r' || nptr[i] == ' ')
		i++;
	if (nptr[i] && nptr[i] == '-')
		i++;
	else if (nptr[i] && nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (nbr > 1844674407370955161 && ft_strlen(nptr) == 20 && \
				nptr[i] - '0' > 5)
			return (0);
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (1);
}

int	ft_exit(char **exit, t_info *info)
{
	int	i;

	i = 0;
	if (exit)
	{
		if (exit[1])
		{
			while (exit[1][i])
			{
				if (is_exiting(exit[1]) || is_too_big(exit[1]) == 0)
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
	}
	ft_putstr_fd("exit\n", 2);
	exit_func(info);
	return (0);
}
