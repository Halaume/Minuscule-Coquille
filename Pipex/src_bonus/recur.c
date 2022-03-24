/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:43:46 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/19 13:08:39 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	recur_pipe(t_struct *pipex, int pipefd)
{
	int	fd[2];

	if (!(pipex->indexarg == (pipex->nb_cmd - 1)))
	{
		if (pipe(fd) < 0)
			error_func(pipex, "Error on pipe\n");
	}
	child(pipex, fd, pipefd);
	if (pipex->indexarg == 0)
		close(fd[1]);
	else if (pipex->indexarg == (pipex->nb_cmd - 1))
		close(pipefd);
	else
	{
		close(fd[1]);
		close(pipefd);
	}
	pipex->indexarg++;
	if (pipex->indexarg < pipex->nb_cmd)
		recur_pipe(pipex, fd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	pipex;
	int			i;

	pipex = check_start(argc, argv, envp);
	pipex.envpath = get_my_path(envp);
	if (pipex.envpath)
		pipex.envpathcut = ft_split(pipex.envpath, ':');
	pipex.indexarg = 0;
	pipex.pid_tab = malloc(sizeof(pid_t) * pipex.nb_cmd);
	if (pipex.fd_in == -1)
		pipex.indexarg++;
	dup2(pipex.fd_in, 0);
	dup2(pipex.fd_out, 1);
	recur_pipe(&pipex, 0);
	i = 0;
	while (i < pipex.nb_cmd)
	{
		wait(&pipex.pid_tab[i]);
		i++;
	}
	free_func(&pipex);
	return (0);
}
