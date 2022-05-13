/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:07:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/13 10:51:53 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	ft_unset(t_info *info, char **commande)
{
	int	i;

	i = 1;
	if (commande[i])
	{
		while (commande[i])
		{
			info->exit_status = ft_unset_this(info, commande[i]);
			i++;
		}
	}
	return (info->exit_status);
}

int	faire(char **cmd, t_info *info, t_toyo *toyo)
{
	if (ft_strlen(cmd[0]) == ft_strlen("echo") && \
			ft_strncmp("echo", cmd[0], ft_strlen(cmd[0])) == 0)
		return (ft_echo(cmd, toyo));
	else if (ft_strlen(cmd[0]) == ft_strlen("pwd") && \
			ft_strncmp("pwd", cmd[0], ft_strlen(cmd[0])) == 0)
		return (ft_pwd());
	else if (ft_strlen(cmd[0]) == ft_strlen("cd") && \
			ft_strncmp("cd", cmd[0], ft_strlen(cmd[0])) == 0)
		return (ft_cd(cmd, info));
	else if (ft_strlen(cmd[0]) == ft_strlen("export") && \
			ft_strncmp("export", cmd[0], ft_strlen(cmd[0])) == 0)
		return (ft_export(info, cmd));
	else if (ft_strlen(cmd[0]) == ft_strlen("unset") && \
			ft_strncmp("unset", cmd[0], ft_strlen(cmd[0])) == 0)
		return (ft_unset(info, cmd));
	else if (ft_strlen(cmd[0]) == ft_strlen("env") && \
			ft_strncmp("env", cmd[0], ft_strlen(cmd[0])) == 0)
		return (ft_env(info->env));
	else if (ft_strlen(cmd[0]) == ft_strlen("exit") && \
			ft_strncmp("exit", cmd[0], ft_strlen(cmd[0])) == 0)
		return (ft_exit(cmd, info));
	return (1);
}

int	is_built_in(t_toyo *toyo, t_info *info)
{
	char	**cmd;
	int		ret;
	char	**tmp_cmd;

	if (!toyo->commande || !*toyo->commande)
		return (1);
	indexeage(toyo->commande, info);
	tmp_cmd = ft_splitsane(toyo->commande, info);
	cmd = add_wildcard(tmp_cmd, info);
	free_char_char(tmp_cmd);
	if (!cmd)
		return (1);
	ret = faire(cmd, info, toyo);
	info->isexport = 0;
	free_char_char(info->envp);
	info->envp = ft_getenvp(info->env);
	free_char_char(cmd);
	return (ret);
}

int	fun_check(char **cmd)
{
	if (!cmd)
		return (1);
	if (ft_strlen(cmd[0]) == ft_strlen("echo") && \
			ft_strncmp("echo", cmd[0], ft_strlen(cmd[0])) == 0)
		return (free_char_char(cmd), 0);
	else if (ft_strlen(cmd[0]) == ft_strlen("pwd") && \
			ft_strncmp("pwd", cmd[0], ft_strlen(cmd[0])) == 0)
		return (free_char_char(cmd), 0);
	else if (ft_strlen(cmd[0]) == ft_strlen("cd") && \
			ft_strncmp("cd", cmd[0], ft_strlen(cmd[0])) == 0)
		return (free_char_char(cmd), 0);
	else if (ft_strlen(cmd[0]) == ft_strlen("export") && \
			ft_strncmp("export", cmd[0], ft_strlen(cmd[0])) == 0)
		return (free_char_char(cmd), 0);
	else if (ft_strlen(cmd[0]) == ft_strlen("unset") && \
			ft_strncmp("unset", cmd[0], ft_strlen(cmd[0])) == 0)
		return (free_char_char(cmd), 0);
	else if (ft_strlen(cmd[0]) == ft_strlen("env") && \
			ft_strncmp("env", cmd[0], ft_strlen(cmd[0])) == 0)
		return (free_char_char(cmd), 0);
	else if (ft_strlen(cmd[0]) == ft_strlen("exit") && \
			ft_strncmp("exit", cmd[0], ft_strlen(cmd[0])) == 0)
		return (free_char_char(cmd), 0);
	return (free_char_char(cmd), 1);
}

int	check_built_in(t_toyo *toyo, t_info *info)
{
	char	*tmp;
	char	**cmd;
	char	**tmp_cmd;

	if (!toyo->commande || !*toyo->commande)
		return (1);
	tmp = ft_strtrim(toyo->commande, " ");
	if (!ft_strncmp(tmp, "export", 6))
		info->isexport = 1;
	free(tmp);
	indexeage(toyo->commande, info);
	tmp_cmd = ft_splitsane(toyo->commande, info);
	cmd = add_wildcard(tmp_cmd, info);
	free_char_char(tmp_cmd);
	return (fun_check(cmd));
}
