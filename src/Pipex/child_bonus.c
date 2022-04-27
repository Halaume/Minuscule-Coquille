/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:34:01 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/27 16:14:02 by ghanquer         ###   ########.fr       */
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
	else if (pipex->indexarg == (pipex->nb_cmd - 1))
		dup2(fd1, 0);
	else
	{
		dup2(fd1, 0);
		dup2(fd[1], 1);
		close(fd[0]);
	}
	if (toyo->in != 0)
		dup2(toyo->in, 0);
	if (toyo->out != 1)
		dup2(toyo->out, 1);
	if (!toyo->commande)
		error_func(pipex, "Command not found\n", "");
	pipex->arg = ft_splitsane(toyo->commande);
}

void	child(t_toyo *toyo, t_struct *pipex, int fd[2], int fd1)
{
	pipex->pid_tab[pipex->indexarg] = fork();
	if (pipex->pid_tab[pipex->indexarg] == 0)
	{
		if (toyo->commande == NULL)
			exit (1);
		duping_closing(toyo, pipex, fd, fd1);
		if (check_built_in(toyo->commande) == 0)
			exit(is_built_in(toyo->commande, pipex->info));
		if (check_abs_path(pipex->arg[0]))
		{
			if (access(pipex->arg[0], X_OK) == 0)
				execve(pipex->arg[0], pipex->arg, pipex->envp);
			else
				error_func(pipex, "Command error\n", pipex->arg[0]);
		}
		else if (pipex->envpath == NULL)
			error_func(pipex, "Command not found\n", pipex->arg[0]);
		if (pipex->envpathcut)
			pipex->cmd = get_cmd(pipex->envpathcut, pipex->arg[0]);
		if (pipex->cmd == NULL)
			error_func(pipex, "command not found\n", pipex->cmd);
		execve(pipex->cmd, pipex->arg, pipex->envp);
		error_func(pipex, "Error", "execve:");
	}
}
