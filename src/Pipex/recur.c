/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:43:46 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/26 14:52:30 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/MinusculeCoquille.h"

void	recur_pipe(t_toyo *toyo, int pipefd, t_struct *pipex)
{
	int	fd[2];

	if (!(pipex->indexarg == (pipex->nb_cmd - 1)))
	{
		if (pipe(fd) < 0)
			return (perror("Error on pipe"), exit(1));
	}
	if (toyo->in != 0)
	{
		close(fd[0]);
		fd[0] = toyo->in;
	}
	if (toyo->out != 1)
	{
		close(fd[1]);
		fd[1] = toyo->out;
	}
	child(toyo, pipex, fd, pipefd);
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
	toyo = toyo->next;
	if (pipex->indexarg < pipex->nb_cmd)
		recur_pipe(toyo, fd[0], pipex);
}

void	nb_toyo_cmd(t_struct *pipex, t_toyo *toyo)
{
	t_toyo *tmp;

	pipex->indexarg = 0;
	pipex->nb_cmd = 0;
	pipex->arg = NULL;
	tmp = toyo;
	while (tmp)
	{
		pipex->nb_cmd++;
		tmp = tmp->next;
	}
	pipex->pid_tab = malloc(sizeof(pid_t) * pipex->nb_cmd);
}

int	toyotage(t_toyo *toyo, t_info *info)
{
	int			i;
	t_struct	pipex;
	int			status;
	t_toyo		*tmp;

	nb_toyo_cmd(&pipex, toyo);
	pipex.envp = info->envp;
	pipex.envpath = get_my_path(info->envp);
	if (pipex.envpath)
		pipex.envpathcut = ft_split(pipex.envpath, ':');
	pipex.indexarg = 0;
	tmp = toyo;
	recur_pipe(tmp, 0, &pipex);
	i = 0;
	while (i < pipex.nb_cmd)
	{
		waitpid(pipex.pid_tab[i], &status, 0);
		i++;
	}
	free_toyo(toyo);
	free_func(&pipex);
	if (WIFEXITED(status))
	{
		info->exit_status = WEXITSTATUS(status);
		return(info->exit_status);
	}
	return (0);
}
