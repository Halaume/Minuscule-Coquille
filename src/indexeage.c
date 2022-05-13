/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexeage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:19:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/13 11:55:58 by tnaton           ###   ########.fr       */
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

void	indexeage2(char *str, t_info *info, int *isex, int *lst)
{
	int		last;
	int		k;
	t_inspi	s;
	int		i;

	kk(&s, &last, &k, &i);
	while (str[i])
	{
		cc(&s, str, i);
		if (str[i] == ' ')
		{
			info->list[k++] = getlist(i, lst, last, s.par);
			while (str[i] == ' ')
				i++;
			last = i - s.par;
		}
		i++;
	}
	info->list[k] = getlist(i, lst, last, s.par);
	free(isex);
	free(lst);
	free(str);
}

void	freelist(int **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

void	indexeage(char *str, t_info *info)
{
	int	*isex;
	int	*lst;
	int	i;
	int	count;

	count = 1;
	i = 0;
	isex = lamort(str, info);
	lst = crie(str, isex, info);
	str = trim_free(re_expand(ft_strdup(str), info), " ");
	while (str[i])
	{
		if (str[i] == ' ')
		{
			count++;
			while (str[i] == ' ')
				i++;
		}
		i++;
	}
	if (info->list)
		freelist(info->list);
	info->list = malloc(sizeof(int *) * (count + 1));
	info->list[count] = NULL;
	indexeage2(str, info, isex, lst);
}
