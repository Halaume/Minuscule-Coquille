/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitsane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:03:35 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/09 16:23:00 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	countword(char *str)
{
	int	insimplegui;
	int	indoublegui;
	int	nbword;
	int	i;

	nbword = 1;
	i = 0;
	insimplegui = 0;
	indoublegui = 0;
	while (str[i])
	{
		if (!indoublegui && str[i] == '\'')
			insimplegui = !insimplegui;
		if (!insimplegui && str[i] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && str[i] == ' ')
		{
			nbword++;
			while (str[i] && str[i] == ' ')
				i++;
		}
		else
			i++;
	}
	return (nbword);
}

char	**ft_splitdesesmorts(char	*str)
{
	char	**dest;
	int		nbword;
	int		i;
	int		j;
	int		insimplegui;
	int		indoublegui;
	int		last;

	j = 0;
	i = 0;
	insimplegui = 0;
	indoublegui = 0;
	nbword = countword(str);
	dest = (char **)malloc(sizeof(char *) * (nbword + 1));
	while (str[i] && str[i] == ' ')
		i++;
	last = i;
	while (str[i])
	{
		if (!indoublegui && str[i] == '\'')
			insimplegui = !insimplegui;
		if (!insimplegui && str[i] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && str[i] == ' ')
		{
			dest[j++] = ft_substr(str, last, i - last);
			while (str[i] && str[i] == ' ')
				i++;
			last = i;
		}
		else
			i++;
	}
	if (last != i)
		dest[j++] = ft_substr(str, last, i - last);
	dest[j] = NULL;
	return (dest);
}

int	countall(char **list)
{
	int	total;
	int	i;

	i = 0;
	total = 0;
	while (list[i])
		total += countword(list[i++]);
	return (total);
}

int	asspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

char	**splitagedesesmorts(char **list, int size)
{
	int		totalword;
	char	**ret;
	char	**tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	totalword = countall(list) + size;
	ret = (char **)malloc(sizeof(char *) * (totalword + 2));
	while (list[i])
	{
		if (asspace(list[i]))
		{
			tmp = ft_splitdesesmorts(list[i]);
			j = 0;
			while (tmp[j])
				ret[k++] = tmp[j++];
			free(tmp);
			free(list[i]);
			i++;
		}
		else
			ret[k++] = list[i++];
	}
	ret[k] = NULL;
	free(list);
	return (ret);
}

char	**ft_splitsane(char	*str, t_info *info)
{
	char	**dest;
	int		nbword;
	int		i;
	int		j;
	int		insimplegui;
	int		indoublegui;
	int		last;
	int		asexpanded;

	j = 0;
	i = 0;
	insimplegui = 0;
	indoublegui = 0;
	nbword = countword(str);
	dest = (char **)malloc(sizeof(char *) * (nbword + 1));
	while (str[i] && str[i] == ' ')
		i++;
	last = i;
	while (str[i])
	{
		if (!indoublegui && str[i] == '\'')
			insimplegui = !insimplegui;
		if (!insimplegui && str[i] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && str[i] == ' ')
		{
			asexpanded = 0;
			dest[j++] = get_del(ft_substr(str, last, i - last), info, \
					&asexpanded);
			if (asexpanded)
			{
				dest[j] = NULL;
				dest = splitagedesesmorts(dest, nbword);
				j = 0;
				while (dest[j])
				{
					if (info->isexport)
						dest[j] = get_del(dest[j], info, NULL);
					j++;
				}
			}
			while (str[i] && str[i] == ' ')
				i++;
			last = i;
		}
		else
			i++;
	}
	if (last != i)
	{
		asexpanded = 0;
		dest[j++] = get_del(ft_substr(str, last, i - last), info, &asexpanded);
		if (asexpanded)
		{		
			dest[j] = NULL;
			dest = splitagedesesmorts(dest, nbword);
			j = 0;
			while (dest[j])
			{
				if (info->isexport)
					dest[j] = get_del(dest[j], info, NULL);
				j++;
			}
		}
	}
	if (dest[j - 1])
		dest[j] = NULL;
	return (dest);
}
