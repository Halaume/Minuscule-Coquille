/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principale3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:12:18 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 16:14:49 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	ft_ischiant(t_arbre *arbre, t_info *info)
{
	char	*tmp;

	if (info->arbre && arbre->fd)
	{
		tmp = ft_strtrim(arbre->fd->commande, " ");
		if (istropchiant(tmp))
			return (free(tmp), 1);
		free(tmp);
	}
	if (info->arbre && arbre->fg)
	{
		tmp = ft_strtrim(arbre->fg->commande, " ");
		if (istropchiant(tmp))
			return (free(tmp), 1);
		free(tmp);
	}
	if ((!arbre->fg || !arbre->fd) && (!ft_strcmp(arbre->commande, "|") \
			|| !ft_strcmp(arbre->commande, "&&") \
				|| !ft_strcmp(arbre->commande, "||")))
		return (1);
	if (!arbre->fg && !arbre->fd)
		return (1);
	return (0);
}

int	ft_istropchiant(t_arbre *arbre, t_info *info)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strtrim(arbre->commande, " ");
	if (istropchiant(tmp))
		return (free(tmp), 1);
	tmp2 = ft_strtrim(tmp, "\"");
	if (info->arbre && !ft_strncmp(tmp2, "<<", 2))
	{
		free(arbre->commande);
		if (info->arbre && asquote(tmp))
			arbre->commande = open_heredoc(ft_strdup(tmp), info);
		else if (info->arbre)
			arbre->commande = open_heredoc(ft_substr(tmp, 2, \
						ft_strlen(tmp) - 2), info);
	}
	free(tmp2);
	free(tmp);
	return (0);
}

int	casseburne(t_arbre *arbre)
{
	char	*tmp;

	tmp = ft_strtrim(arbre->commande, " ");
	if (!ft_strcmp(tmp, ""))
		return (free(tmp), 1);
	return (free(tmp), 0);
}

int	checkarbre(t_arbre *arbre, t_info *info)
{
	if (info->arbre && arbre)
	{
		if (ischiant(arbre))
		{
			if (ft_ischiant(arbre, info))
				return (1);
		}
		else if (info->arbre)
		{
			if (ft_istropchiant(arbre, info))
				return (1);
		}
		if (info->arbre && arbre->fd && arbre->fg)
			return (checkarbre(arbre->fd, info) + checkarbre(arbre->fg, info));
		else if (info->arbre && arbre->fg)
			return (checkarbre(arbre->fg, info));
		else if (info->arbre && arbre->fd)
			return (checkarbre(arbre->fd, info));
		if (info->arbre)
			return (casseburne(arbre));
	}
	return (0);
}

void	movea(t_getenv	*a)
{
	if (a->i == 0)
	{
		a->current = a->tmp;
		a->first = a->current;
	}
	else
	{
		a->current->next = a->tmp;
		a->current = a->current->next;
		a->current->next = NULL;
	}
}
