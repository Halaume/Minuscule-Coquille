/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexeage3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 10:15:46 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/14 10:23:10 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*re_expand(char *str, t_info *info)
{
	char	*newstr;
	t_exp	e;
	char	*tmp;
	int		insimplegui;

	initcaner(&e, &insimplegui);
	newstr = (char *)malloc(sizeof(char) * (refsizeofexheredoc(str, info) + 2));
	while (str[e.i])
	{
		tocard(str, &e, &insimplegui, newstr);
		re_smalex(str, &e.j, &e.i);
		if (e.i != e.j)
		{
			tmp = getvalfromenvhd(ft_substr(str, e.i, e.j - e.i), info, 1, 0);
			e.i = e.j;
			e.j = 0;
			while (tmp[e.j])
				newstr[e.k++] = tmp[e.j++];
			free(tmp);
		}
	}
	free(str);
	newstr[e.k] = '\0';
	return (newstr);
}

int	aaaaa(char *str, int *isex, t_info *info)
{
	int	i;
	int	simplegui;
	int	doublegui;
	int	count;

	i = 0;
	count = 0;
	simplegui = 0;
	doublegui = 0;
	str = re_expand(ft_strdup(str), info);
	while (str && str[i])
	{
		if (!isex[i] && !simplegui && str[i] == '"')
			doublegui = !doublegui;
		if (!isex[i] && !doublegui && str[i] == '\'')
			simplegui = !simplegui;
		if ((doublegui || simplegui) && !isex[i] && str[i] == '*')
			count++;
		i++;
	}
	free(str);
	return (count);
}

void	lamourir(char *str, t_info *info, int *isex, t_exp *s)
{
	int		ret;
	char	*tmp;

	ret = s->i;
	s->i++;
	while (isadel(str, s->i))
	{
		if (s->i && str[s->i - 1] == '?')
			break ;
		s->i++;
	}
	tmp = getvalfromenvhd(ft_substr(str, ret, s->i - ret), info, 1, 0);
	ret = 0;
	while (tmp[ret])
	{
		isex[s->j] = 1;
		ret++;
		s->j++;
	}
	free(tmp);
}

int	*lamort(char *str, t_info *info)
{
	int		*isex;
	t_exp	s;
	char	*tmp;

	s.k = 0;
	s.i = 0;
	s.j = 0;
	tmp = re_expand(ft_strdup(str), info);
	isex = malloc(sizeof(int) * (ft_strlen(tmp) + 1));
	free(tmp);
	while (str[s.i])
	{
		if (str[s.i] == '\'')
			s.k = !s.k;
		if (!s.k && str[s.i] == '$')
			lamourir(str, info, isex, &s);
		else
		{
			isex[s.j] = 0;
			s.i++;
			s.j++;
		}
	}
	isex[s.j] = -1;
	return (isex);
}

void	initcrie(t_inspi *s, int *i, int *j)
{
	s->doublegui = 0;
	s->simplegui = 0;
	s->par = 0;
	*i = 0;
	*j = 0;
}
