/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_name_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:20:23 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/13 14:21:41 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

t_name	*new_lst(char *str, int type)
{
	t_name	*new;

	new = NULL;
	new = malloc(sizeof(t_name));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->type = type;
	new->name = str;
	return (new);
}

t_name	*lst_last(t_name *lst)
{
	t_name	*current;

	current = lst;
	if (!current)
		return (NULL);
	if (!current->next)
		return (current);
	while (current->next)
		current = current->next;
	return (current);
}

void	lst_add(t_name **alst, t_name *new)
{
	t_name	*tmp;

	if (alst)
	{
		if (*alst)
		{
			tmp = lst_last(*alst);
			tmp->next = new;
		}
		else
			*alst = new;
	}
}

void	free_name(t_name *list)
{
	t_name	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->name);
		free(list);
		list = NULL;
		list = tmp;
	}
}
