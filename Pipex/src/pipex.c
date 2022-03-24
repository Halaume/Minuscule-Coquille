/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:19:57 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/22 10:46:33 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*get_my_path(char **envp)
{
	while (*envp && ft_strncmp("PATH=", *envp, 5) != 0)
	{
		envp++;
		if (envp == NULL)
			return (NULL);
	}
	if (!*envp)
		return (NULL);
	return (*envp + 5);
}

t_struct	init_pipex(void)
{
	t_struct	pipex;

	pipex.envpath = NULL;
	pipex.envpathcut = NULL;
	pipex.arg = NULL;
	pipex.cmd = NULL;
	pipex.fd_in = -1;
	pipex.fd_out = -1;
	pipex.forkcmd1 = -1000;
	pipex.forkcmd2 = -1000;
	pipex.exec_return = 1;
	return (pipex);
}

char	*get_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	if (path)
	{
		while (path[i])
		{
			tmp = ft_join(path[i], "/");
			command = ft_join(tmp, cmd);
			free(tmp);
			if (access(command, X_OK) == 0)
				return (command);
			free(command);
			i++;
		}
	}
	return (NULL);
}

void	first_fun(t_struct *pipex, char **argv, char **envp)
{
	dup2(pipex->ma_pipe[1], 1);
	dup2(pipex->fd_in, 0);
	close(pipex->ma_pipe[0]);
	pipex->arg = ft_split(argv[2], ' ');
	if (check_abs_path(argv, 2))
	{
		if (access(pipex->arg[0], X_OK) == 0)
			execve(pipex->arg[0], pipex->arg, envp);
		else
			error_func(pipex, "Command error\n");
	}
	pipex->cmd = get_cmd(pipex->envpathcut, pipex->arg[0]);
	if (pipex->cmd == NULL)
		perror("command error");
	execve(pipex->cmd, pipex->arg, envp);
	error_func(pipex, "execve\n");
}

void	second_fun(t_struct *pipex, char **argv, char **envp)
{
	dup2(pipex->ma_pipe[0], 0);
	dup2(pipex->fd_out, 1);
	close(pipex->ma_pipe[1]);
	pipex->arg = ft_split(argv[3], ' ');
	if (check_abs_path(argv, 3))
	{
		if (access(pipex->arg[0], X_OK) == 0)
			execve(pipex->arg[0], pipex->arg, envp);
		else
			error_func(pipex, "Command error\n");
	}
	if (pipex->envpathcut)
		pipex->cmd = get_cmd(pipex->envpathcut, pipex->arg[0]);
	if (pipex->cmd == NULL)
		error_func(pipex, "Command error\n");
	close(pipex->ma_pipe[0]);
	execve(pipex->cmd, pipex->arg, envp);
	error_func(pipex, "execve\n");
}
