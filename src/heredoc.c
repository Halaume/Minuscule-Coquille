/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:58:20 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 15:29:53 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*newchar(char *str)
{
	int	num;

	num = ft_atoi(str);
	num++;
	free(str);
	return (ft_itoa(num));
}

char	*checkopen(char *str)
{
	int		ret;
	char	*tmp;

	ret = 0;
	while (!ret)
	{
		tmp = ft_strjoin("/tmp/.", str);
		ret = access(tmp, F_OK);
		if (!ret)
		{
			free(tmp);
			str = newchar(str);
		}
	}
	free(str);
	return (tmp);
}

int	isinlist(int num, int *list)
{
	int	i;

	i = 1;
	while (i < list[0] + 1)
	{
		if (list[i] == num)
			return (1);
		i++;
	}
	return (0);
}

char	*rmquote(char *del, int *list)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(del) - list[0] + 1));
	i = 0;
	j = 0;
	while (del[i])
	{
		if (!isinlist(i, list))
			tmp[j++] = del[i++];
		else
			i++;
	}
	tmp[j] = '\0';
	free(del);
	free(list);
	return (tmp);
}
