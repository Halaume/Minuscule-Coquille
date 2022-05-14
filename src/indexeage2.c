/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexeage2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 10:15:48 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/14 10:16:17 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

void	prout(char *str, t_exp *e, int *insimplegui)
{
	while (str[e->i])
	{
		if (!*insimplegui && str[e->i] == '$')
			break ;
		if (str[e->i] == '\'')
			*insimplegui = !*insimplegui;
		e->i++;
		e->k++;
	}
}

int	refsizeofexheredoc(char *str, t_info *info)
{
	t_exp	e;
	int		insimplegui;

	insimplegui = 0;
	e.i = 0;
	e.k = 0;
	while (str[e.i])
	{
		prout(str, &e, &insimplegui);
		e.j = e.i;
		if (str[e.j] == '$')
			e.j++;
		while (isadel(str, e.j))
		{
			if (e.j && str[e.j - 1] == '?')
				break ;
			e.j++;
		}
		if (e.i != e.j)
			crever(&e, info, str);
	}
	return (e.k);
}

void	re_smalex(char *str, int *j, int *i)
{
	*j = *i;
	if (str[*j] == '$')
		(*j)++;
	while (isadel(str, *j))
	{
		if (*j && str[*j - 1] == '?')
			break ;
		(*j)++;
	}
}

void	tocard(char *str, t_exp *e, int *insimplegui, char *newstr)
{
	while (str[e->i])
	{
		if (!*insimplegui && str[e->i] == '$')
			break ;
		if (str[e->i] == '\'')
			*insimplegui = !*insimplegui;
		newstr[e->k] = str[e->i];
		e->k++;
		e->i++;
	}
}

void	initcaner(t_exp *e, int *gui)
{
	*gui = 0;
	e->i = 0;
	e->k = 0;
}
