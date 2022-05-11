/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:27:16 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 15:28:19 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	isdelgood(char *str, int i)
{
	return (str[i] && (((str[i] >= 'A' && str[i] <= 'Z') \
					|| (str[i] >= 'a' && str[i] <= 'z') || (str[i] == '$')) \
			|| (i && str[i] == '?' && str[i - 1] == '$')));
}

void	pf(char *ret, char *del, int *j, int *i)
{
	while (*j < *i)
	{
		ret[*j] = del[*j];
		(*j)++;
	}
}

char	*changedel(char *del, int *i, t_info *info, int ingui)
{
	char	*ret;
	int		lenexpanded;
	int		j;
	int		souvenir;

	souvenir = *i;
	j = 0;
	lenexpanded = getfuturesizeoftheexpandedshit(del, *i, info, ingui);
	ret = (char *)malloc(sizeof(char *) * (ft_strlen(del) + lenexpanded));
	pf(ret, del, &j, i);
	while (isdelgood(del, *i))
	{
		if ((souvenir != *i && del[*i] == '$') || (*i && del[*i - 1] == '?'))
			break ;
		*i += 1;
	}
	ret[j] = '\0';
	ret = ft_strjoin_free(ret, getvalfromenv(ft_substr(del, j, *i - j), info, \
				ingui, del[*i]));
	ret = ft_strjoin_free(ret, ft_substr(del, *i, ft_strlen(del) - *i));
	*i = souvenir + lenexpanded - 1;
	return (free(del), ret);
}

void	initshit(int *i, int *j, int *insimplegui, int *indoublegui)
{
	*i = 0;
	*j = 1;
	*insimplegui = 0;
	*indoublegui = 0;
}

char	*get_del(char *del, t_info *info, int *asex, int caca)
{
	t_del	d;
	char	*tmp;
	int		par;

	par = 0;
	tmp = trim_free(del, " ");
	del = tmp;
	d.list = (int *)malloc(sizeof(int) * (ft_strlen(del) + 1));
	initshit(&d.i, &d.j, &d.sg, &d.dg);
	while (del[d.i])
	{
		gui(del[d.i], &d.dg, &d.sg, &par);
		if ((!d.sg && del[d.i] == '"') || (!d.dg && del[d.i] == '\''))
			d.list[d.j++] = d.i;
		if (caca && (!d.sg && del[d.i] == '$'))
		{
			*asex = 1;
			del = changedel(del, &d.i, info, (d.sg || d.dg));
			if (!ft_strlen(del))
				break ;
		}
		d.i++;
	}
	d.list[0] = d.j - 1;
	return (rmquote(del, d.list));
}
