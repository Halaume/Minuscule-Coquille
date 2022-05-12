/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:48:58 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/12 12:15:30 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*jc(char *s1, char *s2)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	while (*s1)
	{
		dest[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		dest[i++] = *s2;
		s2++;
	}
	dest[i] = '\0';
	return (dest);
}

int	check_wildcard(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '*')
				return (1);
			i++;
		}
	}
	return (0);
}

int	norme_good(char *arg, char *str, int i, int j)
{
	while (arg[j] && str[i])
	{
		if (arg[j] == '*')
		{
			if (arg[j + 1] == '\0')
				return (0);
			while (str[i] && ft_strncmp(arg + j + 1, str + i, \
						lbs(arg + j + 1)) != 0)
			{
				i++;
				if (str[i] == '\0' && arg[j + 1 + (lbs(arg + j + 1))] != '\0')
					return (0);
				else if (str[i] == '\0')
					return (1);
			}
			i--;
		}
		else if (str[i] != arg[j])
			return (1);
		i++;
		j++;
	}
	if (!arg[j] && str[i])
		return (1);
	return (0);
}

int	is_good_word(char *arg, char *str/*, int p_max*/)
{
	if (!arg || !str)
		return (1);
	return (norme_good(arg, str, 0, 0));
}

int	nb_of_good_word(char *arg, t_name *name/*, int p_max*/)
{
	int		i;
	t_name	*tmp;

	tmp = name;
	i = 0;
	while (tmp)
	{
		if (is_good_word(arg, tmp->name/*, p_max*/) == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
