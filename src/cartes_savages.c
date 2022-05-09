/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_savages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:52:53 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/09 16:24:17 by ghanquer         ###   ########.fr       */
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

char	**norme_carte(char *arg, char **ret, t_name *fichier)
{
	int		nb_word;
	int		i;
	t_name	*tmp;

	nb_word = nb_of_good_word(arg, fichier);
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

char	**cartes_sauvages(char *arg)
{
	DIR				*my_dir;
	char			**ret;
	struct dirent	*reading;
	t_name			*fichier;
	int				i;

	reading = NULL;
	ret = NULL;
	fichier = NULL;
	i = 0;
	my_dir = opendir(".");
	if (!my_dir)
		return (perror("Wildcards: "), NULL);
	reading = readdir(my_dir);
	while (reading != NULL)
	{
		i++;
		lst_add(&fichier, new_lst(ft_strdup(reading->d_name)));
		reading = readdir(my_dir);
	}
	ret = norme_carte(arg, ret, fichier);
	free_name(fichier);
	closedir(my_dir);
	return (ret);
}

int	count_wildcards(char **arg)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (arg[i])
	{
		ret += lencaca(cartes_sauvages(arg[i]));
		i++;
	}
	return (ret);
}

char	**add_wildcard(char **cmd)
{
	char	**tmp;
	char	**tmp2;
	int		j;
	int		k;
	int		index;
	int		i;

	k = count_wildcards(cmd);
	j = 0;
	i = 0;
	index = 0;
	tmp = malloc(sizeof(char *) * (k + 1));
	while (cmd[index])
	{
		tmp2 = cartes_sauvages(cmd[index]);
		i = 0;
		while (tmp2[i])
		{
			tmp[j] = ft_strdup(tmp2[i]);
			j++;
			i++;
		}
		if (tmp2)
			free_char_char(tmp2);
		index++;
	}
	tmp[j] = NULL;
	return (tmp);
}
