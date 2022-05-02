/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_name_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:20:23 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/02 16:30:52 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

void	lst_add(char *str, t_name *list)
{
	t_name	*tmp;

	tmp = NULL;
	if (list->name == NULL)
	{
		list->name = str;
		return ;
	}
	tmp = malloc(sizeof(t_name));
	if (!tmp)
	{
		perror("Malloc lst_name : ");
		return ;
	}
	tmp->name = str;
	tmp->next = NULL;
	list->next = tmp;
}
