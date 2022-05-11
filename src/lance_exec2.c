/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lance_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:53:08 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 15:56:13 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	get_fd_concat(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 2, ft_strlen(path) - 2);
	fd = open(tmp, O_APPEND | O_WRONLY | O_CREAT, 00644);
	free(tmp);
	return (fd);
}

int	get_fd_out(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 1, ft_strlen(path) - 1);
	fd = open(tmp, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	free(tmp);
	return (fd);
}

int	get_fd_in(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 1, ft_strlen(path) - 1);
	fd = open(tmp, O_RDONLY);
	free(tmp);
	return (fd);
}

char	*getvalfromenvhd(char *var, t_info *info, int ingui, char next)
{
	t_env	*current;

	if (!ft_strcmp(var, "$?"))
		return (free(var), ft_itoa(info->exit_status));
	if (!ft_strcmp(var, "$") && (ingui || next == ' ' || next == '\0' \
				|| next == '$'))
		return (free(var), ft_strdup("$"));
	else if (!ft_strcmp(var, "$"))
		return (free(var), ft_strdup(""));
	current = info->env;
	while (current && ft_strcmp(var + 1, current->variable))
		current = current->next;
	free(var);
	if (!current)
		return (ft_strdup(""));
	return (ft_strdup(current->valeur));
}

int	isadel(char *str, int j)
{
	return (str[j] && ((str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= 'a' \
						&& str[j] <= 'z') || (str[j - 1] == '$' && \
							str[j] == '?')));
}
