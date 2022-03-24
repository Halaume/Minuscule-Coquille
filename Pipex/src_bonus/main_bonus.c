/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:58:49 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/19 12:53:32 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	check_abs_path(char **argv, int j)
{
	int	i;

	i = 0;
	if (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] == '/' && argv[j][i - 1] && argv[j][i - 1] != '\\')
				return (1);
			i++;
		}
	}
	return (0);
}

void	get_infile(char **argv, t_struct *pipex, int argc)
{
	if (!ft_strncmp("here_doc", argv[1], ft_strlen(argv[1])))
	{
		pipex->is_heredoc = 1;
		pipex->nb_cmd = argc - 3 - pipex->is_heredoc;
		pipex->nb_pipe = 2 * (pipex->nb_cmd - 1);
		fun_here_doc(argv[2], pipex);
	}
	else
	{
		pipex->is_heredoc = 0;
		pipex->nb_cmd = argc - 3;
		pipex->fd_in = open(argv[1], O_RDONLY);
		if (pipex->fd_in < 0)
			ft_putstr("Open fd_in Error\n");
	}
}

t_struct	check_start(int argc, char **argv, char **envp)
{
	t_struct	pipex;

	if (argc < args_min(argv[1], &pipex))
		exit(1);
	pipex = init_pipex(argv, envp);
	get_infile(argv, &pipex, argc);
	get_outfile(argv[argc - 1], &pipex);
	return (pipex);
}
