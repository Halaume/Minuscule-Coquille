/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_savages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:52:53 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/14 10:00:11 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	is_good_fic(struct dirent *str, char *arg)
{
	if (str->d_name[0] == '.' && arg[0] == '.')
		return (0);
	if (str->d_name[0] != '.' && arg[0] != '.')
		return (0);
	if (str->d_type == DT_DIR && arg[ft_strlen(arg) - 1] == '/')
		return (0);
	if (str->d_type != DT_DIR && arg[ft_strlen(arg) - 1] != '/')
		return (0);
	return (1);
}

int	ispoint(struct dirent *str, char *arg)
{
	if (str->d_name[0] == '.' && arg[0] == '.')
		return (1);
	if (str->d_name[0] != '.' && arg[0] != '.')
		return (1);
	return (0);
}

int	isslash(struct dirent *str, char *arg)
{
	if (str->d_type == DT_DIR && arg[ft_strlen(arg) - 1] == '/')
		return (1);
	if (arg[ft_strlen(arg) - 1] != '/')
		return (1);
	return (0);
}

int	opening(char *dirname, t_name **fic, char *arg)
{
	t_ouvrir	o;

	o.my_dir = opendir(dirname);
	o.rd = NULL;
	if (!o.my_dir)
		return (perror("Wildcards "), 1);
	o.rd = readdir(o.my_dir);
	while (o.rd != NULL)
	{
		if (ispoint(o.rd, arg) && isslash(o.rd, arg))
		{
			if (arg[ft_strlen(arg) - 1] == '/')
				lst_add(fic, new_lst(jc((o.rd->d_name), "/"), o.rd->d_type));
			else
				lst_add(fic, new_lst(ft_strdup(o.rd->d_name), o.rd->d_type));
		}
		o.rd = readdir(o.my_dir);
	}
	return (closedir(o.my_dir), 0);
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
	if (opening(".", &fichier, arg) == 1)
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


