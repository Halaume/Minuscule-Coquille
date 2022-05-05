/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:47:02 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/05 15:13:34 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

void	exit_func(t_info *info)
{
	freearbre(info->arbre);
	freeenv(info->env);
	free_char_char(info->envp);
	rl_clear_history();
	exit(info->exit_status);
}

void	free_toyo(t_toyo *toyo)
{
	t_toyo	*current;

	current = toyo;
	while (current)
	{
		toyo = current;
		current = current->next;
		free(toyo);
	}
	free(current);
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
