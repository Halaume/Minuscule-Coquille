/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:29:20 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 15:29:36 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*quoteit(char	*str)
{
	char	*tmp;

	tmp = ft_strjoin("\"", str);
	free(str);
	str = ft_strjoin(tmp, "\"");
	free(tmp);
	return (str);
}

char	*getisexp(char *var, t_info *info, int ingui, char next)
{
	t_env	*current;

	if (!ft_strcmp(var, "$?"))
		return (free(var), quoteit(ft_itoa(info->exit_status)));
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
	return (quoteit(ft_strdup(current->valeur)));
}

char	*getisnotexp(char *var, t_info *info, int ingui, char next)
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

char	*getvalfromenv(char *var, t_info *info, int ingui, char next)
{
	if (info->isexport)
		return (getisexp(var, info, ingui, next));
	else
		return (getisnotexp(var, info, ingui, next));
}

int	getfuturesizeoftheexpandedshit(char *del, int i, t_info *info, int ingui)
{
	int		j;
	char	*var;

	j = i;
	while (del[j] && ((del[j] >= 'A' && del[j] <= 'Z') \
				|| (del[j] >= 'a' && del[j] <= 'z') || (del[j] == '$' \
					|| del[j] == '?')))
	{
		if (j != i && del[j] == '$')
			break ;
		j++;
	}
	var = ft_substr(del, i, j - i);
	var = getvalfromenv(var, info, ingui, del[j]);
	j = ft_strlen(var);
	return (free(var), j);
}
