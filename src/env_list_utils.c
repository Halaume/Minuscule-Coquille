/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 10:56:42 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/08 10:57:17 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

t_env	*new_env(char *str, char *valeur)
{
	t_env	*new;

	new = NULL;
	new = malloc(sizeof(t_env));
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
