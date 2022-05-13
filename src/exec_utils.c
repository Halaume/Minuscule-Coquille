/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:15:11 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/13 10:10:24 by ghanquer         ###   ########.fr       */
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
	if (path && *cmd)
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

void	norme_executing(t_toyo *toyo, t_info *info, char **arg)
{
	char	*env;
	char	*cmd;

	env = NULL;
	cmd = NULL;
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
	perror("execve failure :");
}

int	executing(t_toyo *toyo, t_info *info)
{
	char	**arg;
	char	**tmp_arg;

	indexeage(toyo->commande, info);
	tmp_arg = ft_splitsane(toyo->commande, info);
/*	int i = 0;
	int j = 0;
	while (tmp_arg[i])
	{
		printf("tmp_arg : %s", tmp_arg[i]);
		j = 0;
		while (info->list[i][j] != -1)
			printf(" %d", info->list[i][j++]);
		printf("\n");
		i++;
	}*/
	arg = add_wildcard(tmp_arg, info);
	free_char_char(tmp_arg);
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
	norme_executing(toyo, info, arg);
	exit(1);
}
