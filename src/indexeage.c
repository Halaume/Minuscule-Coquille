/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexeage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:19:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/14 10:18:46 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

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
