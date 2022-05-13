/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:48:58 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/13 18:58:58 by ghanquer         ###   ########.fr       */
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

int	ft_strcmp_free(char *s1, char *s2)
{
	int	i;
	int	ret;

	i = 0;
	while (s1[i] == s2[i])
	{
		i++;
		if (s1[i] == '\0')
			return (free(s1), 0);
	}
	ret = *(unsigned char *)s1 - *(unsigned char *)--s2;
	free(s1);
	return (ret);
}

int	norme_good(char *arg, t_name *fic, int *list, int i)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '*' && osef(list, j) != 1)
		{
			while (arg[j + 1] == '*')
				j++;
			if (arg[j + 1] == '\0')
			{
				return (0);
			}
			if (!fic->name[i])
				return (1);
			while (fic->name[i] && (ft_strcmp_free(ft_substr(arg, j + 1, lbs(arg + j + 1)), fic->name + i) != 0))
			{
				printf("%s | %s\n", ft_substr(arg, j + 1, lbs(arg + j + 1)), fic->name + i);
				if (norme_good2(i++, j + 1, fic, arg) != -1)
					return (norme_good2(i, j + 1, fic, arg));
				printf("retour cmp = %d\n", ft_strcmp_free(ft_substr(arg, j + 1, lbs(arg + j + 1)), fic->name + i));
			}
			if (ft_strcmp_free(ft_substr(arg, j + 1, lbs(arg + j + 1)), fic->name + i))
				i--;
			else if (arg[j + 1 + lbs(arg + j + 1)] == '\0')
			{
				if (ft_strlen(fic->name + i) == (size_t)lbs(arg + j))
					return (0);
//				return (0);
			}
			else
				i--;
		}
		else if (fic->name[i] != arg[j])
			return (1);
		i++;
		j++;
	}
//	printf("arg[j - 1] = %c, fic->name[i] = %c\narg = %s, fic->name = %s\n", arg[j - 1], fic->name[i], arg, fic->name);
	if (arg[j - 1] && fic->name[i] != arg[j - 1])
		return (1);
	if (!arg[j] && fic->name[i + 1])
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
