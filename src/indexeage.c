/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexeage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:19:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/13 11:04:17 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	refsizeofexheredoc(char *str, t_info *info)
{
	t_exp	e;
	int		insimplegui;

	insimplegui = 0;
	e.i = 0;
	e.k = 0;
	while (str[e.i])
	{
		while (str[e.i])
		{
			if (!insimplegui && str[e.i] == '$')
				break ;
			if (str[e.i] == '\'')
				insimplegui = !insimplegui;
			e.i++;
			e.k++;
		}
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

char	*re_expand(char *str, t_info *info)
{
	char	*newstr;
	t_exp	e;
	char	*tmp;
	int		insimplegui;

	e.i = 0;
	e.k = 0;
	insimplegui = 0;
	newstr = (char *)malloc(sizeof(char) * (refsizeofexheredoc(str, info) + 2));
	while (str[e.i])
	{
		while (str[e.i])
		{
			if (!insimplegui && str[e.i] == '$')
				break ;
			if (str[e.i] == '\'')
				insimplegui = !insimplegui;
			newstr[e.k] = str[e.i];
			e.k++;
			e.i++;
		}
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

int	*lamort(char *str, t_info *info)
{
	int		*isex;
	int		i;
	int		j;
	int		ret;
	int		simplegui;
	char	*tmp;

	simplegui = 0;
	i = 0;
	j = 0;
	tmp = re_expand(ft_strdup(str), info);
	isex = malloc(sizeof(int) * (ft_strlen(tmp) + 1));
	while (str[i])
	{
		if (str[i] == '\'')
			simplegui = !simplegui;
		if (!simplegui && str[i] == '$')
		{
			ret = i;
			i++;
			while (isadel(str, i))
			{
				if (i && str[i - 1] == '?')
					break ;
				i++;
			}
			free(tmp);
			tmp = getvalfromenvhd(ft_substr(str, ret, i - ret), info, 1, 0);
			ret = 0;
			while (tmp[ret])
			{
				isex[j] = 1;
				ret++;
				j++;
			}
		}
		else
		{
			isex[j] = 0;
			i++;
			j++;
		}
	}
	isex[j] = -1;
	free(tmp);
	return (isex);
}

int	*crie(char *str, int *isex, t_info *info)
{
	int	*lst;
	int	i;
	int	simplegui;
	int	doublegui;
	int	countgui;
	int	j;

	doublegui = 0;
	simplegui = 0;
	countgui = 0;
	i = 0;
	j = 0;
	lst = malloc(sizeof(int) * (aaaaa(str, isex, info) + 1));
	lst[aaaaa(str, isex, info)] = -1;
	str = re_expand(ft_strdup(str), info);
	while (str[i])
	{
		if (!isex[i] && !simplegui && str[i] == '"')
		{
			countgui++;
			doublegui = !doublegui;
		}
		if (!isex[i] && !doublegui && str[i] == '\'')
		{
			countgui++;
			simplegui = !simplegui;
		}
		if (!isex[i] && (simplegui || doublegui) && str[i] == '*')
			lst[j++] = i - countgui;
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

void	indexeage2(char *str, t_info *info, int *isex, int *lst)
{
	int	last;
	int	k;
	int	doublegui;
	int	simplegui;
	int	countgui;
	int	i;

	last = 0;
	k = 0;
	doublegui = 0;
	simplegui = 0;
	countgui = 0;
	i = 0;
	while (str[i])
	{
		if (!simplegui && str[i] == '"')
		{
			countgui++;
			doublegui = !doublegui;
		}
		if (!doublegui && str[i] == '\'')
		{
			countgui++;
			simplegui = !simplegui;
		}
		if (str[i] == ' ')
		{
			info->list[k++] = getlist(i, lst, last, countgui);
			while (str[i] == ' ')
				i++;
			last = i - countgui;
		}
		i++;
	}
	info->list[k] = getlist(i, lst, last, countgui);
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
	str = re_expand(ft_strdup(str), info);
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
