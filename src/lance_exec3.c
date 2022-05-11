/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lance_exec3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:53:55 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 15:54:24 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

void	crever(t_exp *e, t_info *info, char *str)
{
	char	*tmp;

	tmp = getvalfromenvhd(ft_substr(str, e->i, e->j - e->i), info, 1, 0);
	e->k += ft_strlen(tmp);
	free(tmp);
	e->i = e->j;
}

int	fsizeofexheredoc(char *str, t_info *info)
{
	t_exp	e;

	e.i = 0;
	e.k = 0;
	while (str[e.i])
	{
		while (str[e.i] && str[e.i] != '$')
		{
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

void	smalex(char *str, int *j, int *i)
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

char	*expand(char *str, t_info *info)
{
	char	*newstr;
	t_exp	e;
	char	*tmp;

	e.i = 0;
	e.k = 0;
	newstr = (char *)malloc(sizeof(char) * (fsizeofexheredoc(str, info) + 2));
	while (str[e.i])
	{
		while (str[e.i] && str[e.i] != '$')
			newstr[e.k++] = str[e.i++];
		smalex(str, &e.j, &e.i);
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

void	ecrit(int fd, int fd2, t_info *info)
{
	char	*tmp;

	tmp = ft_strdup("ah");
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
		if (tmp)
		{
			tmp = expand(tmp, info);
			write (fd2, tmp, ft_strlen(tmp));
		}
	}
}
