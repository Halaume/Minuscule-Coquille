/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_savages_norme.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 09:59:42 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/14 10:00:09 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	count_wildcards(char **arg, int **list)
{
	int		i;
	int		ret;
	char	**test;

	i = 0;
	ret = 0;
	while (arg[i])
	{
		test = cartes_sauvages(arg[i], list[i]);
		ret += lencaca(test);
		if (test)
			free_char_char(test);
		i++;
	}
	return (ret);
}

char	**add_wildcard(char **cmd, t_info *info)
{
	char	**tmp;
	char	**tmp2;
	int		j;
	int		index;
	int		i;

	j = 0;
	index = -1;
	tmp = malloc(sizeof(char *) * (count_wildcards(cmd, info->list) + 1));
	while (cmd[++index])
	{
		tmp2 = cartes_sauvages(cmd[index], info->list[index]);
		i = -1;
		if (tmp2)
		{
			while (tmp2[++i])
			{
				tmp[j] = ft_strdup(tmp2[i]);
				j++;
			}
			free_char_char(tmp2);
		}
	}
	tmp[j] = NULL;
	return (tmp);
}
