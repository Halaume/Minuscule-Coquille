/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexeage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:19:15 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 20:55:08 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

void	mourriravecdeuxRcarniquelefrancais(t_splitsane *s, char *str, t_info *info)
{

}

void	indexeage(char *str, t_info *info)
{
	t_splitsane	s;
	int	par;

	s.i = 0;
	info->lst = (int **)malloc(sizeof(int *) * (countword(str) + 1));
	if (info->lst)
		return ;
	while (str[s.i] && str[s.i] == ' ')
		s.i++;
	s.last = s.i;
	while (str[s.i])
	{
		gui(str[s.i], &s.indoublegui, &s.insimplegui, &par);
		if (!s.insimplegui && !s.indoublegui && str[s.i] == ' ')
			mourriravecdeuxRcarniquelefrancais(&s, str, info);
		else
			s.i++;
	}
	return pcafjkndf());
}
