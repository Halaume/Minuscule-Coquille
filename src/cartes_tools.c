/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:04:32 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/12 12:12:20 by ghanquer         ###   ########.fr       */
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

char	**norme_carte(char *arg, char **ret, t_name *fichier)
{
	int		nb_word;
	int		i;
	t_name	*tmp;

	nb_word = nb_of_good_word(arg, fichier, count_prof(arg));
	ret = malloc(sizeof(char *) * (nb_word + 1));
	if (!ret)
		return (NULL);
	ret[nb_of_good_word(arg, fichier)] = NULL;
	tmp = fichier;
	i = 0;
	while (tmp && i < nb_word)
	{
		if (is_good_word(arg, tmp->name) == 0)
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
