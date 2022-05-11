/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitsane_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:34:42 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/11 15:09:40 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	countword(char *str)
{
	int	insimplegui;
	int	indoublegui;
	int	nbword;
	int	i;

	nbword = 1;
	i = 0;
	insimplegui = 0;
	indoublegui = 0;
	while (str[i])
	{
		if (!indoublegui && str[i] == '\'')
			insimplegui = !insimplegui;
		if (!insimplegui && str[i] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && str[i] == ' ')
		{
			nbword++;
			while (str[i] && str[i] == ' ')
				i++;
		}
		else
			i++;
	}
	return (nbword);
}

char	**ft_splitdesesmorts(char	*str)
{
	char	**dest;
	t_sdsm	s;

	init_sdsm(&s, str);
	dest = (char **)malloc(sizeof(char *) * (s.nbword + 1));
	while (str[s.i] && str[s.i] == ' ')
		s.i++;
	s.last = s.i;
	while (str[s.i])
	{
		gui(str[s.i], &s.indoublegui, &s.insimplegui, &s.par);
		if (!s.insimplegui && !s.indoublegui && str[s.i] == ' ')
		{
			dest[s.j++] = ft_substr(str, s.last, s.i - s.last);
			while (str[s.i] && str[s.i] == ' ')
				s.i++;
			s.last = s.i;
		}
		else
			s.i++;
	}
	if (s.last != s.i)
		dest[s.j++] = ft_substr(str, s.last, s.i - s.last);
	dest[s.j] = NULL;
	return (dest);
}

int	countall(char **list)
{
	int	total;
	int	i;

	i = 0;
	total = 0;
	while (list[i])
		total += countword(list[i++]);
	return (total);
}

int	asspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	initsplit(t_del *d, char **list, int size)
{
	d->i = 0;
	d->sg = 0;
	d->dg = countall(list) + size;
}
