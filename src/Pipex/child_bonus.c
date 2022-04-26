/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:34:01 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/26 13:11:35 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/MinusculeCoquille.h"

void	duping_closing(t_toyo *toyo, t_struct *pipex, int fd[2], int fd1)
{
	if (pipex->indexarg == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
	}
	else if (pipex->indexarg == pipex->nb_cmd - 1)
		dup2(fd1, 0);
	else
	{
		dup2(fd1, 0);
		dup2(fd[1], 1);
		close(fd[0]);
	}
	if (!toyo->commande)
		error_func(pipex, "Command not found");
	pipex->arg = ft_splitsane(toyo->commande);
}

void	child(t_toyo *toyo, t_struct *pipex, int fd[2], int fd1)
{
	pipex->pid_tab[pipex->indexarg] = fork();
	if (pipex->pid_tab[pipex->indexarg] == 0)
	{
		duping_closing(toyo, pipex, fd, fd1);
		if (check_abs_path(toyo->commande))
		{
			if (access(pipex->arg[0], X_OK) == 0)
				execve(pipex->arg[0], \
						pipex->arg, pipex->envp);
			else
			{
				perror("Command error");
				error_func(pipex, "");
			}
		}
		else if (pipex->envpath == NULL)
			error_func(pipex, "Command not found\n");
		if (pipex->envpathcut)
			pipex->cmd = get_cmd(pipex->envpathcut, pipex->arg[0]);
		if (pipex->cmd == NULL)
			error_func(pipex, "command not found");
		execve(pipex->cmd, pipex->arg, pipex->envp);
		error_func(pipex, "execve");
	}
}
