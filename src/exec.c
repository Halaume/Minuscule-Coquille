/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:19:57 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/25 15:10:27 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*get_my_path(char **envp)
{
	while (*envp && ft_strncmp("PATH=", *envp, 5) != 0)
	{
		if (*envp == NULL)
			return (NULL);
		envp++;
	}
	if (!*envp)
		return (NULL);
	return (*envp + 5);
}

int	check_abs_path(char *argv)
{
	int	i;

	i = 0;
	if (argv[0] == '/')
		return (1);
	return (0);
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
			tmp = ft_strjoin(path[i], "/");
			command = ft_strjoin(tmp, cmd);
			free(tmp);
			if (access(command, X_OK) == 0)
				return (command);
			if (command)
				free(command);
			i++;
		}
	}
	return (NULL);
}

int	executing(t_toyo *toyo, t_info *info)
{
	char	**arg;
	char	*env;
	char	*cmd;

	env = NULL;
	arg = NULL;
	cmd = NULL;
	dup2(toyo->in, 0);
	dup2(toyo->out, 1);
	arg = ft_split(toyo->commande, ' ');
	if (check_abs_path(toyo->commande))
	{
		if (access(arg[0], X_OK) == 0)
			execve(arg[0], arg, info->envp);
		else
		{
			perror("Command error");
			free(arg);
			exit(1);
		}
	}
	env = get_my_path(info->envp);
	cmd = get_cmd(ft_split(env, ':'), arg[0]);
	if (cmd == NULL)
	{
		perror("command error");
		free(arg);
		exit(1);
	}
	execve(cmd, arg, info->envp);
	perror("execve\n");
	return (1);
}

int	exec(t_toyo *toyo, t_info *info)
{
	pid_t	my_pid;
	int		status;

	status = check_built_in(toyo->commande);
	if (status == 0)
		return (is_built_in(toyo->commande,info->envp));
	my_pid = fork();
	if (my_pid < 0)
		return (write(2, "fork error\n", 12), -1);
	if (my_pid == 0)
		executing(toyo, info);
	waitpid(my_pid, &status, 0);
	free_toyo(toyo);
	if (WIFEXITED(status))
	{
		info->exit_status = WEXITSTATUS(status);
		return(info->exit_status);
	}
	return(0);
}
