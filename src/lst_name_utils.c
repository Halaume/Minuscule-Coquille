/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_name_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:20:23 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/06 11:40:11 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

t_name	*new_lst(char *str)
{
	t_name *new;

	new = NULL;
	new = malloc(sizeof(t_name));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->name = str;
	return (new);
}

t_name	*lst_last(t_name *lst)
{
	t_name	*current;

	current = lst;
	if (!current)
		return (NULL);
	if (!current -> next)
		return (current);
	while (current -> next)
		current = current -> next;
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

t_env	*new_env(char *str, char *valeur)
{
	t_env *new;

	new = NULL;
	new = malloc(sizeof(t_name));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->variable = str;
	new->valeur = valeur;
	return (new);
}

t_env	*env_last(t_env *lst)
{
	t_env	*current;

	current = lst;
	if (!current)
		return (NULL);
	if (!current -> next)
		return (current);
	while (current -> next)
		current = current -> next;
	return (current);
}

void	env_add(t_env **alst, t_env *new)
{
	t_env	*tmp;

	if (alst)
	{
		if (*alst)
		{
			tmp = env_last(*alst);
			tmp->next = new;
		}
		else
			*alst = new;
	}
}

