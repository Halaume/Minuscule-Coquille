/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitsane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:03:35 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/10 20:12:34 by tnaton           ###   ########.fr       */
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

void	init_sdsm(t_sdsm *s, char *str)
{
	s->j = 0;
	s->i = 0;
	s->insimplegui = 0;
	s->indoublegui = 0;
	s->nbword = countword(str);
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
		gui(str[s.i], &s.indoublegui, &s.insimplegui, NULL);
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

char	**splitagedesesmorts(char **list, int size)
{
	t_del	d;
	char	**ret;
	char	**tmp;

	initsplit(&d, list, size);
	ret = (char **)malloc(sizeof(char *) * (d.dg + 2));
	while (list[d.i])
	{
		if (asspace(list[d.i]))
		{
			tmp = ft_splitdesesmorts(list[d.i]);
			d.j = 0;
			while (tmp[d.j])
				ret[d.sg++] = tmp[d.j++];
			free(tmp);
			free(list[d.i]);
			d.i++;
		}
		else
			ret[d.sg++] = list[d.i++];
	}
	ret[d.sg] = NULL;
	free(list);
	return (ret);
}

void	initsplitsane(t_splitsane *s, char *str)
{
	s->j = 0;
	s->i = 0;
	s->insimplegui = 0;
	s->indoublegui = 0;
	s->nbword = countword(str);
	s->dest = (char **)malloc(sizeof(char *) * (s->nbword + 1));
}

char	**reft_splitsane(t_splitsane *s, char *str, t_info *info)
{
	if (s->last != s->i)
	{
		s->asexpanded = 0;
		s->dest[s->j++] = get_del(ft_substr(str, s->last, s->i - s->last), \
				info, &s->asexpanded, 1);
		if (s->asexpanded)
		{		
			s->dest[s->j] = NULL;
			s->dest = splitagedesesmorts(s->dest, s->nbword);
			s->j = 0;
			while (s->dest[s->j])
			{
				if (info->isexport)
					s->dest[s->j] = get_del(s->dest[s->j], info, NULL, 1);
				s->j++;
			}
		}
	}
	if (s->dest[s->j - 1])
		s->dest[s->j] = NULL;
	return (s->dest);
}

void	mid_splitsane(t_splitsane *s, char *str, t_info *info)
{
	s->asexpanded = 0;
	s->dest[s->j++] = get_del(ft_substr(str, s->last, s->i - s->last), info, \
			&s->asexpanded, 1);
	if (s->asexpanded)
	{
		s->dest[s->j] = NULL;
		s->dest = splitagedesesmorts(s->dest, s->nbword);
		s->j = 0;
		while (s->dest[s->j])
		{
			if (info->isexport)
				s->dest[s->j] = get_del(s->dest[s->j], info, NULL, 1);
			s->j++;
		}
	}
	while (str[s->i] && str[s->i] == ' ')
		s->i++;
	s->last = s->i;
}

char	**ft_splitsane(char	*str, t_info *info)
{
	t_splitsane	s;

	initsplitsane(&s, str);
	while (str[s.i] && str[s.i] == ' ')
		s.i++;
	s.last = s.i;
	while (str[s.i])
	{
		gui(str[s.i], &s.indoublegui, &s.insimplegui, NULL);
		if (!s.insimplegui && !s.indoublegui && str[s.i] == ' ')
			mid_splitsane(&s, str, info);
		else
			s.i++;
	}
	return (reft_splitsane(&s, str, info));
}
