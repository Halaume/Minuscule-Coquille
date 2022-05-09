/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_savages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:52:53 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/09 12:09:40 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	len_before_star(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '*')
		i++;
	return (i);
}

int	is_good_word(char *arg, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!arg || !str)
		return (1);
	while (arg[j] && str[i])
	{
		if (arg[j] == '*')
		{
			if (arg[j + 1] == '\0')
				return (0);
			while (str[i] && ft_strncmp(arg + j + 1, str + i, \
						len_before_star(arg + j + 1)) != 0)
			{
				i++;
				if (str[i] == '\0' && arg[j + 1 + \
						len_before_star(arg + j + 1)] != '\0')
					return (0);
				else if (str[i] == '\0')
					return (1);
			}
		}
		else if (str[i] != arg[j])
			return (0);
		i++;
		j++;
	}
	return (0);
}

int	nb_of_good_word(char *arg, t_name *name)
{
	int		i;
	t_name	*tmp;

	tmp = name;
	i = 0;
	while (tmp)
	{
		if (is_good_word(arg, tmp->name) == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**norme_carte(t_name *tmp, char *arg, char **ret, t_name *fichier)
{
	int	nb_word;
	int	i;

	nb_word = nb_of_good_word(arg, fichier);
	ret = malloc(sizeof(char *) * (nb_word + 1));
	if (!ret)
		return (NULL);
	ret[nb_of_good_word(arg, fichier)] = "\0";
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

char	**cartes_sauvages(char *arg)
{
	DIR				*my_dir;
	char			**ret;
	struct dirent	*reading;
	t_name			*fichier;
	t_name			*tmp;
	int				i;

	reading = NULL;
	ret = NULL;
	fichier = NULL;
	i = 0;
	my_dir = opendir(".");
	if (!my_dir)
		return (perror("Wildcards: "), NULL);
	while (reading != NULL || i == 0)
	{
		i++;
		reading = readdir(my_dir);
		lst_add(&fichier, new_lst(ft_strdup(reading->d_name)));
	}
	ret = norme_carte(tmp, arg, ret, fichier);
	free_name(fichier);
	free(arg);
	closedir(my_dir);
	return (ret);
}
