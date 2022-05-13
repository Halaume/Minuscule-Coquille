/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_savages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:52:53 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/13 11:06:47 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	opening(char *dirname, t_name **fic, int prof, int p_max)
{
	t_ouvrir	o;

	o.i = 0;
	o.my_dir = opendir(dirname);
	o.dp = ft_strjoin(dirname, "/");
	o.rd = NULL;
	if (!o.my_dir)
		return (perror("Wildcards "), 1);
	o.rd = readdir(o.my_dir);
	while (o.rd != NULL)
	{
		o.i++;
		if (o.rd->d_type == DT_DIR && ft_strncmp(o.rd->d_name, ".", 2) != 0 && \
				ft_strncmp(o.rd->d_name, "..", 3) != 0 && prof < p_max)
		{
			if (opening(o.rd->d_name, fic, 1, prof + 1) == 1)
				return (free(o.dp), closedir(o.my_dir), 1);
		}
		else if (ft_strncmp(o.rd->d_name, ".", 1) != 0 && \
				ft_strncmp(o.rd->d_name, "..", 2) != 0 && prof == p_max)
			lst_add(fic, new_lst(trim_free(jc(o.dp, o.rd->d_name), "./")));
		o.rd = readdir(o.my_dir);
	}
	return (free(o.dp), closedir(o.my_dir), 0);
}

char	**cartes_sauvages(char *arg, int *list)
{
	char			**ret;
	t_name			*fichier;

	if (!check_wildcard(arg))
	{
		ret = malloc(sizeof(char *) * 2);
		ret[0] = ft_strdup(arg);
		ret[1] = NULL;
		return (ret);
	}
	ret = NULL;
	fichier = NULL;
	if (opening(".", &fichier, 0, count_prof(arg)) == 1)
		return (NULL);
	if (nb_of_good_word(arg, fichier, list) == 0)
	{
		ret = malloc(sizeof(char *) * 2);
		free_name(fichier);
		ret[0] = ft_strdup(arg);
		ret[1] = NULL;
		return (ret);
	}
	ret = norme_carte(arg, ret, fichier, list);
	free_name(fichier);
	return (ret);
}

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
