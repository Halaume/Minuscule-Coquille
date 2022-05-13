/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:47:02 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/13 12:45:44 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

void	exit_func(t_info *info)
{
	freearbre(info->arbre);
	info->arbre = NULL;
	freeenv(info->env);
	free_char_char(info->envp);
	rl_clear_history();
	if (info->list)
		freelist(info->list);
	exit(info->exit_status);
}

void	free_toyo(t_toyo *toyo)
{
	t_toyo	*current;

	if (toyo)
	{
		current = toyo;
		while (current)
		{
			toyo = current;
			current = current->next;
			free(toyo);
		}
		free(current);
	}
}

void	free_char_char(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str[i]);
		free(str);
	}
}
