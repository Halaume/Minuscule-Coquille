/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lance_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:43:00 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 15:56:03 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	lancet(t_arbre *arbre, t_info *info)
{
	if (!lance_exec(info, arbre->fd))
	{
		if (info->arbre)
			return (lance_exec(info, arbre->fg));
		return (0);
	}
	else
	{
		if (info->arbre)
			return (badet(info, arbre->fg));
		return (0);
	}
}

int	lance_exec(t_info *info, t_arbre *arbre)
{
	if (arbre && !info->caner)
	{
		if (!ft_strcmp(arbre->commande, "&&"))
			return (lancet(arbre, info));
		else if (!ft_strcmp(arbre->commande, "||"))
		{
			if (lance_exec(info, arbre->fd))
			{
				if (info->arbre)
					return (lance_exec(info, arbre->fg));
				return (0);
			}
			else
			{
				if (info->arbre)
					return (badou(info, arbre->fg));
				return (0);
			}
		}
		else if (!ft_strcmp(arbre->commande, "|"))
			return (toyotage(rec_toyo(arbre, info), info));
		if (info->arbre)
			return (exec(getcommande(arbre, info), info));
	}
	return (info->exit_status);
}
