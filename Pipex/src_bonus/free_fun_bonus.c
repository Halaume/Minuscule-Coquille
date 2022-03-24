/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fun_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:34:08 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/19 12:48:33 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	free_func(t_struct *pipex)
{
	int	i;

	i = -1;
	if (pipex->fd_in)
		close(pipex->fd_in);
	if (pipex->fd_out)
		close(pipex->fd_out);
	if (pipex->arg)
		while (pipex->arg[++i])
			free(pipex->arg[i]);
	if (pipex->arg)
		free(pipex->arg);
	i = -1;
	if (pipex->envpathcut)
		while (pipex->envpathcut[++i])
			free(pipex->envpathcut[i]);
	if (pipex->envpathcut)
		free(pipex->envpathcut);
	if (pipex->cmd)
		free(pipex->cmd);
	if (pipex->pid_tab)
		free(pipex->pid_tab);
	if (pipex->is_heredoc)
		unlink(".heredoc_tmp");
}

void	error_func(t_struct *pipex, char *msg)
{
	free_func(pipex);
	ft_putstr(msg);
	exit(1);
}
