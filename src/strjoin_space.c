/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:57:11 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/22 10:02:00 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*strjoin_space(char *s1, char *s2)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!dest)
		return (NULL);
	if (*s1)
	{
		while (*s1)
		{
			dest[i++] = *s1;
			s1++;
		}
		if (*s2)
		{
			dest[i] = ' ';
			i++;
		}
	}
	while (*s2)
	{
		dest[i++] = *s2;
		s2++;
	}
//	if (s1)
//		free(s1);
	dest[i] = '\0';
	return (dest);
}
