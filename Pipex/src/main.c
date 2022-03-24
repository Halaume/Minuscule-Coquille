/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:58:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/23 15:14:05 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_func(t_struct *pipex)
{
	int	i;

	i = -1;
	if (pipex->fd_in)
		close(pipex->fd_in);
	if (pipex->fd_out)
		close(pipex->fd_out);
	if (pipex->ma_pipe[0])
		close(pipex->ma_pipe[0]);
	if (pipex->ma_pipe[1])
		close(pipex->ma_pipe[1]);
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
}

int	check_abs_path(char **argv, int j)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[j][i] == '/' && argv[j][i - 1] && argv[j][i - 1] != '\\')
			return (1);
		i++;
	}
	return (0);
}

void	error_func(t_struct *pipex, char *msg)
{
	free_func(pipex);
	ft_putstr(msg);
	exit(1);
}

t_struct	check_start(int argc, char **argv, char **envp)
{
	t_struct	pipex;

	if (argc != 5 || !envp[0])
		exit(1);
	pipex = init_pipex();
	pipex.fd_in = open(argv[1], O_RDONLY);
	if (pipex.fd_in < 0)
		perror("open fd_in error");
	if (pipe(pipex.ma_pipe) == -1)
		error_func(&pipex, "pipe");
	pipex.envpath = get_my_path(envp);
	return (pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	pipex;

	pipex = check_start(argc, argv, envp);
	if (pipex.envpath)
		pipex.envpathcut = ft_split(pipex.envpath, ':');
	if (pipex.fd_in >= 0)
		pipex.forkcmd1 = fork();
	if (pipex.forkcmd1 == -1)
		error_func(&pipex, "forkcmd1 error\n");
	if (pipex.forkcmd1 == 0)
		first_fun(&pipex, argv, envp);
	else
		do_my_sec_fork(argc, argv, &pipex, envp);
	close(pipex.ma_pipe[1]);
	waitpid(pipex.forkcmd2, NULL, 0);
	close(pipex.ma_pipe[0]);
	waitpid(pipex.forkcmd1, NULL, 0);
	free_func(&pipex);
	return (0);
}
