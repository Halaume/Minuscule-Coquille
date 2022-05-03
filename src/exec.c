/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:19:57 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/03 16:53:52 by tnaton           ###   ########.fr       */
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
	if (ft_strchr(argv, '/'))
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
				return (free_char_char(path), command);
			if (command)
				free(command);
			i++;
		}
	}
	return (free_char_char(path), NULL);
}

int	executing(t_toyo *toyo, t_info *info)
{
	char	**arg;
	char	*env;
	char	*cmd;

	env = NULL;
	arg = NULL;
	cmd = NULL;
	arg = ft_splitsane(toyo->commande, info);
	if (check_abs_path(arg[0]))
	{
		if (access(arg[0], X_OK) == 0)
			execve(arg[0], arg, info->envp);
		else
		{
			ft_putstr_fd(arg[0], 2);
			ft_putstr_fd(": Command error\n", 2);
			free_toyo(toyo);
			free_char_char(arg);
			exit(1);
		}
	}
	env = get_my_path(info->envp);
	cmd = get_cmd(ft_split(env, ':'), arg[0]);
	if (cmd == NULL)
	{
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": Command not found\n", 2);
		free_toyo(toyo);
		free_char_char(arg);
		exit(1);
	}
	execve(cmd, arg, info->envp);
	perror("execve");
	return (1);
}

int	exec(t_toyo *toyo, t_info *info)
{
	pid_t	my_pid;
	int		status;
	pid_t	forking;

	if (!toyo->commande)
		return (free_toyo(toyo), 1);
	if (!ft_strncmp("()", toyo->commande, 2))
	{
		forking = fork();
		if (forking == 0)
		{
			lance_exec(info, toyo->arbre);
			exit(info->exit_status);
		}
		waitpid(forking, &status, 0);
		free_toyo(toyo);
		return (status);
	}
	if (toyo == NULL)
		return (info->exit_status);
	status = check_built_in(toyo->commande, info);
	if (status == 0)
	{
		info->exit_status = is_built_in(toyo->commande,info);
		free_toyo(toyo);
		return (info->exit_status);
	}
	my_pid = fork();
	if (my_pid < 0)
		return (write(2, "fork error\n", 12), -1);
	if (my_pid == 0)
	{
		dup2(toyo->in, 0);
		dup2(toyo->out, 1);
		executing(toyo, info);
	}
	waitpid(my_pid, &status, 0);
	free_toyo(toyo);
	if (WIFEXITED(status))
	{
		info->exit_status = WEXITSTATUS(status);
		return(info->exit_status);
	}
	return (0);
}
