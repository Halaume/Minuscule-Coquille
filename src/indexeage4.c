/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexeage4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 10:18:14 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/14 10:18:38 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

void	hurle(int *isex, int i, t_inspi *s, char *str)
{
	if (!isex[i] && !s->simplegui && str[i] == '"')
	{
		s->par++;
		s->doublegui = !s->doublegui;
	}
	if (!isex[i] && !s->doublegui && str[i] == '\'')
	{
		s->par++;
		s->simplegui = !s->simplegui;
	}
}

int	*crie(char *str, int *isex, t_info *info)
{
	int		*lst;
	int		i;
	t_inspi	s;
	int		j;

	initcrie(&s, &i, &j);
	lst = malloc(sizeof(int) * (aaaaa(str, isex, info) + 1));
	lst[aaaaa(str, isex, info)] = -1;
	str = re_expand(ft_strdup(str), info);
	while (str[i])
	{
		hurle(isex, i, &s, str);
		if (!isex[i] && (s.simplegui || s.doublegui) && str[i] == '*')
			lst[j++] = i - s.par;
		i++;
	}
	free(str);
	return (lst);
}

int	*getlist(int i, int *lst, int last, int countgui)
{
	int	*ret;
	int	j;
	int	k;

	k = 0;
	j = 0;
	while (lst[j] != -1)
	{
		if (lst[j] >= last && lst[j] < i - countgui)
			k++;
		j++;
	}
	ret = malloc(sizeof(int) * (k + 1));
	ret[k] = -1;
	j = 0;
	k = 0;
	while (lst[j] != -1)
	{
		if (lst[j] >= last && lst[j] < i - countgui)
			ret[k++] = lst[j] - last;
		j++;
	}
	return (ret);
}

void	kk(t_inspi *s, int *last, int *k, int *i)
{
	*last = 0;
	*k = 0;
	s->doublegui = 0;
	s->simplegui = 0;
	s->par = 0;
	*i = 0;
}

void	cc(t_inspi *s, char *str, int i)
{
	if (!s->simplegui && str[i] == '"')
	{
		s->par++;
		s->doublegui = !s->doublegui;
	}
	if (!s->doublegui && str[i] == '\'')
	{
		s->par++;
		s->simplegui = !s->simplegui;
	}
}
