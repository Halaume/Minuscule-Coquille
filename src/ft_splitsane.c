/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitsane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:03:35 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/26 12:40:56 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	countword(char *str)
{
	int	insimplegui;
	int	indoublegui;
	int	nbword;
	int i;

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

char	**ft_splitsane(char	*str)
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
	last = 0;
	insimplegui = 0;
	indoublegui = 0;
	nbword = countword(str);
	printf("%d\n", nbword);
	dest = (char **)malloc(sizeof(char *) * (nbword + 1));
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
