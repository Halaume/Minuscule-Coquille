/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lance_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:43:00 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/24 12:20:29 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MinusculeCoquille.h"

int	lance_exec(t_info *info, t_arbre *arbre)
{
	if (!ft_strcmp(arbre->commande, "&&"))
		if (lance_exec(info, arbre->fd))
			lance_exec(info, arbre->fg);
	if (!ft_strcmp(arbre->commande, "||"))
		if (!lance_exec(info, arbre->fd))
			lance_exec(info, arbre->fg);
	if (!ft_strcmp(arbre->commande, "|"))
	{

	}
}
