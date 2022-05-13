/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:34:01 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/13 11:46:11 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/MinusculeCoquille.h"

void	duping_closing(t_toyo *toyo, t_struct *pipex, int fd[2], t_info *info)
{
//	char	**tmp_cmd;

	if (pipex->indexarg == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
	}
	else if (pipex->indexarg == (pipex->nb_cmd - 1))
		dup2(pipex->fd1, 0);
	else
	{
		dup2(pipex->fd1, 0);
		dup2(fd[1], 1);
		close(fd[0]);
	}
	if (toyo->in != 0)
		dup2(toyo->in, 0);
	if (toyo->out != 1)
		dup2(toyo->out, 1);
	if (!toyo->commande)
		error_func(pipex, "Command not found\n", "");
/*	indexeage(toyo->commande, info);
	tmp_cmd = ft_splitsane(toyo->commande, info);
	pipex->arg = add_wildcard(tmp_cmd, info);
	free_char_char(tmp_cmd);*/
	pipex->arg = ft_splitsane(toyo->commande, info);
}

void	child_checking(t_toyo *toyo, t_info *info, t_struct *pipex)
{
	if (check_built_in(toyo, info) == 0)
		exit(is_built_in(toyo, pipex->info));
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
}

void	child(t_toyo *toyo, t_struct *pipex, int fd[2], t_info *info)
{
	pipex->pid_tab[pipex->indexarg] = fork();
	if (pipex->pid_tab[pipex->indexarg] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (toyo->commande == NULL)
			exit (1);
		duping_closing(toyo, pipex, fd, info);
		if (!ft_strncmp("()", toyo->commande, 2))
		{
			lance_exec(pipex->info, toyo->arbre);
			exit(pipex->info->exit_status);
		}
		child_checking(toyo, info, pipex);
		execve(pipex->cmd, pipex->arg, pipex->envp);
		error_func(pipex, "Error", "execve:");
	}
}
