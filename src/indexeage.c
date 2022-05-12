/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexeage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:19:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/12 12:58:49 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int		aaaaa(char *str, int *isex)
{
	int	i;
	int	countgui;
	int	doublegui;
	int	simplegui;
	int	par;
	int	count;

	i = 0;
	count = 0;
	countgui = 0;
	doublegui = 0;
	simplegui = 0;
	par = 0;
	while (str[i])
	{
		if (!isex && ((!doublegui && str[i] == '\'') || (!simplegui && str[i] == '"')))
			countgui++;
		gui(str[i], &doublegui, &simplegui, &par);
		if (!doublegui && !simplegui && !isex[i] && str[i] == '*')
			count++;
		i++;
	}
	printf("countgui : %d\n", countgui);
	printf("count : %d\n", count);
	return (count);
}

int		*lamort(char *str, t_info *info)
{
	int	*isex;
	int	i;
	int	j;
	int	ret;
	int	simplegui;
	char	*tmp;

	simplegui = 0;
	i = 0;
	j = 0;
	tmp = expand(ft_strdup(str), info);
	if (ft_strlen(tmp) < ft_strlen(str))
		tmp = str;
	printf("expanded >%s<\n", tmp);
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
			printf("str : >%s<\nret : %d | i : %d\n", str, ret, i);
			tmp = getvalfromenvhd(ft_substr(str, ret, i - ret), info, 1, 0);
			printf("tmp : >%s<\n", tmp);
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
	printf("j : %d\n", j);
	isex[j] = -1;
	i = 0;
	while (isex[i] != -1)
		printf("%d", isex[i++]);
	printf("\n");
	return (isex);
}

int	*crie(char *str, int *isex)
{
	int	*lst;

	lst = malloc(sizeof(int) * (aaaaa(str, isex) + 1));
	lst[aaaaa(str, isex)] = -1;
	return (lst);
}

void	indexeage(char *str, t_info *info)
{
	int	*isex;
	int	*lst;

	isex = lamort(str, info);
	lst = crie(str, isex);
}
