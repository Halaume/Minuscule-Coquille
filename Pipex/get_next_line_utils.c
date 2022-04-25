/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:35:15 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/06 16:34:13 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
			i++;
	}
	return (i);
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	else
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (0);
			i++;
		}
	}
	return (1);
}

int	fill_line(char *line, char *buffer, int j, int i)
{
	if (line)
	{
		while (line[++i])
		{
			buffer[j] = line[i];
			j++;
		}
	}
	return (j);
}
