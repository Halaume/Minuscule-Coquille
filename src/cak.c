/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cak.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:11:13 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/13 21:58:12 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	sheesh(char *str, t_sheesh *s, int *list)
{
	if (str[s->i] == '*' && !osef(list, s->i))
	{
		if (!str[++s->i])
			return (1);
		s->tmp = s->i;
		s->tmpfile = s->file + 1;
	}
	else if (str[s->i] == *s->file)
	{
		s->i++;
		s->file++;
	}
	else
	{
		s->i = s->tmp;
		s->file = s->tmpfile++;
	}
	return (0);
}

int	canwork(char *str, char *fic, int *list)
{
	t_sheesh	s;

	s.i = 0;
	s.file = fic;
	while (*s.file && (str[s.i] != '*' || osef(list, s.i)))
	{
		if (str[s.i] != *s.file)
			return (0);
		s.i++;
		s.file++;
	}
	while (*s.file)
		if (sheesh(str, &s, list))
			return (1);
	while (str[s.i] == '*' && !osef(list, s.i))
		s.i++;
	return (!str[s.i]);
}

int	potage(char *str, t_name *file, int *list)
{
	return (!canwork(str, file->name, list));
}
