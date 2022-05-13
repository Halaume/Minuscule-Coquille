/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:04:32 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/13 11:06:24 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	lbs(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	return (i);
}

char	**norme_carte(char *arg, char **ret, t_name *fichier, int *list)
{
	int		nb_word;
	int		i;
	t_name	*tmp;

	nb_word = nb_of_good_word(arg, fichier, list);
	ret = malloc(sizeof(char *) * (nb_word + 1));
	if (!ret)
		return (NULL);
	ret[nb_of_good_word(arg, fichier, list)] = NULL;
	tmp = fichier;
	i = 0;
	while (tmp && i < nb_word)
	{
		if (is_good_word(arg, tmp->name, list) == 0)
		{
			ret[i] = ft_strdup(tmp->name);
			i++;
		}
		tmp = tmp->next;
	}
	return (ret);
}

int	count_prof(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '/')
				count++;
			i++;
		}
	}
	return (count);
}

int	osef(int *lst, int i)
{
	int	j;

	j = 0;
	while (lst[j] != -1)
	{
		if (lst[j] == i)
			return (1);
		j++;
	}
	return (0);
}
