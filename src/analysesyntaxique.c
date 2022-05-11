/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 15:40:26 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*vireconcat(char *str, t_info *info)
{
	char	*tmp;
	int		asex;

	tmp = ft_strtrim(str, " >");
	free(str);
	str = get_del(tmp, info, &asex, 1);
	if (!ft_strlen(str) && asex)
		return (free(str), NULL);
	tmp = ft_strjoin(">>", str);
	free(str);
	return (tmp);
}

char	*vireout(char *str, t_info *info)
{
	char	*tmp;
	int		asex;

	tmp = ft_strtrim(str, " >");
	free(str);
	str = get_del(tmp, info, &asex, 1);
	if (!ft_strlen(str) && asex)
		return (free(str), NULL);
	tmp = ft_strjoin(">", str);
	free(str);
	return (tmp);
}

char	*virehere(char *str, t_info *info)
{
	char	*tmp;
	int		quote;
	int		asex;

	tmp = ft_strtrim(str, " <");
	quote = asquote(tmp);
	free(str);
	str = get_del(tmp, info, &asex, 0);
	if (!ft_strlen(str) && asex)
		return (free(str), NULL);
	tmp = ft_strjoin("<<", str);
	if (quote)
	{
		free(str);
		str = ft_strjoin("\"", tmp);
		free(tmp);
		tmp = ft_strjoin(str, "\"");
	}
	free(str);
	return (tmp);
}

char	*virein(char *str, t_info *info)
{
	char	*tmp;
	int		asex;

	tmp = ft_strtrim(str, " <");
	free(str);
	str = get_del(tmp, info, &asex, 1);
	if (!ft_strlen(str) && asex)
		return (free(str), NULL);
	tmp = ft_strjoin("<", str);
	free(str);
	return (tmp);
}
