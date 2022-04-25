/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:47:02 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/25 14:40:35 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	exit_func(int status)
{
	//	TODO
	//	FREE ALL
	return (status);
}

void	free_toyo(t_toyo *toyo)
{
	t_toyo *current;

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
