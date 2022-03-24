/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:19:57 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/19 12:53:23 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

char	*get_my_path(char **envp)
{
	while (*envp && ft_strncmp("PATH", *envp, 4) != 0)
	{
		envp++;
		if (envp == NULL)
			return (NULL);
	}
	if (!*envp)
		return (NULL);
	return (*envp + 5);
}

t_struct	init_pipex(char **argv, char **envp)
{
	t_struct	pipex;

	pipex.envpath = NULL;
	pipex.envpathcut = NULL;
	pipex.arg = NULL;
	pipex.cmd = NULL;
	pipex.pid_tab = NULL;
	pipex.argv = argv;
	pipex.envp = envp;
	pipex.fd_in = -1;
	pipex.fd_out = -1;
	return (pipex);
}

char	*get_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
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
	return (NULL);
}

void	get_outfile(char *argv, t_struct *pipex)
{
	if (pipex->is_heredoc == 1)
		pipex->fd_out = open(argv, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		pipex->fd_out = open(argv, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out < 0)
		error_func(pipex, "Open fd_out error\n");
}

int	args_min(char *arg, t_struct *pipex)
{
	if (arg && !ft_strncmp("here_doc", arg, ft_strlen(arg)))
	{
		pipex->is_heredoc = 1;
		return (6);
	}
	else
	{
		pipex->is_heredoc = 0;
		return (5);
	}
}
