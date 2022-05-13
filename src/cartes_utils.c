/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:48:58 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/13 14:38:19 by ghanquer         ###   ########.fr       */
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

int	norme_good(char *arg, t_name *fic, int *list, int i)
{
	int	j;

	j = 0;
	while (arg[j] && fic->name[i])
	{
		if (arg[j] == '*' && !osef(list, j))
		{
			if (arg[j + 1] == '\0')
				return (0);
			while (fic->name[i] && ft_strncmp(arg + j + 1, fic->name + i, \
						lbs(arg + j + 1)) != 0)
			{
				if (norme_good2(i++, j, fic, arg) != -1)
					return (norme_good2(i, j, fic, arg));
			}
			i--;
		}
		else if (fic->name[i] != arg[j])
			return (1);
		i++;
		j++;
	}
	if (!arg[j] && fic->name[i])
		return (1);
	return (0);
}

int	is_good_word(char *arg, t_name *fic, int *list)
{
	if (!arg || !fic->name)
		return (1);
	return (norme_good(arg, fic, list, 0));
}

int	nb_of_good_word(char *arg, t_name *name, int *list)
{
	int		i;
	t_name	*tmp;

	tmp = name;
	i = 0;
	while (tmp)
	{
		if (is_good_word(arg, tmp, list) == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
