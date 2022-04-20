
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:19:57 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/22 10:46:33 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

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

int	check_abs_path(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '/' && argv[i - 1] && argv[i - 1] != '\\')
			return (1);
		i++;
	}
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
			free(command);
			i++;
		}
	}
	return (NULL);
}

int	executing(char *commande, char **envp)
{
	char	**arg;
	char	*env;
	char	*cmd;

	env = NULL;
	arg = NULL;
	cmd = NULL;
	arg = ft_split(commande, ' ');
	if (check_abs_path(commande))
	{
		if (access(arg[0], X_OK) == 0)
			execve(arg[0], arg, envp);
		else
		{
			perror("Command error\n");
			free(arg);
			exit(1);
		}
	}
	env = get_my_path(envp);
	cmd = get_cmd(ft_split(env, ':'), arg[0]);
	if (cmd == NULL)
	{
		perror("command error");
		free(arg);
		free(env);
		exit(1);
	}
	execve(cmd, arg, envp);
	perror("execve\n");
	return (1);
}

int	exec(char *commande, char **envp)
{
	pid_t	my_pid;
	int		status;

	status = check_built_in(commande);
	if (status == 0)
		return (is_built_in(commande));
	my_pid = fork();
	if (my_pid < 0)
		return (write(2, "fork error\n", 12), -1);
	if (my_pid == 0)
		executing(commande, envp);
	waitpid(my_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return(0);
}
