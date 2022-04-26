/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fun_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:34:08 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/26 14:53:22 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/MinusculeCoquille.h"

void	free_func(t_struct *pipex)
{
	int	i;

	i = -1;
	if (pipex->envpathcut)
		while (pipex->envpathcut[++i])
			free(pipex->envpathcut[i]);
	if (pipex->envpathcut)
		free(pipex->envpathcut);
	if (pipex->pid_tab)
		free(pipex->pid_tab);
}

void	error_func(t_struct *pipex, char *msg)
{
	free_func(pipex);
	(void)pipex;
	ft_putstr_fd(msg, 2);
	exit(1);
}
