/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_savages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:52:53 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/10 15:17:51 by ghanquer         ###   ########.fr       */
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
						(len_before_star(arg + j + 1))] != '\0')
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

int	opening(char *dirname, t_name **fichier, int profondeur, int prof_max)
{
	DIR				*my_dir;
	struct dirent	*reading;
	char			*dirpath;
	int				i;

	i = 0;
	my_dir = opendir(dirname);
	dirpath = ft_strjoin(dirname, "/");
	reading = NULL;
	if (!my_dir)
		return (perror("Wildcards "), 1);
	reading = readdir(my_dir);
	while (reading != NULL)
	{
		i++;
		if (reading->d_type == DT_DIR && ft_strncmp(reading->d_name, ".", 2) != 0 && ft_strncmp(reading->d_name, "..", 3) != 0 && profondeur < prof_max)
		{
			if (opening(reading->d_name, fichier, 1, profondeur + 1) == 1)
				return (free(dirpath), 1);
		}
		else
			lst_add(fichier, new_lst(ft_strtrim(ft_strjoin(dirpath, reading->d_name), "./")));
		reading = readdir(my_dir);
	}
	free(dirpath);
	closedir(my_dir);
	return (0);
}

char	**cartes_sauvages(char *arg)
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
	if (nb_of_good_word(arg, fichier) == 0)
	{
		ret = malloc(sizeof(char *) * 2);
		free_name(fichier);
		ret[0] = ft_strdup(arg);
		ret[1] = NULL;
		return (ret);
	}
	ret = norme_carte(arg, ret, fichier);
	free_name(fichier);
	return (ret);
}

int	count_wildcards(char **arg)
{
	int		i;
	int		ret;
	char	**test;

	i = 0;
	ret = 0;
	while (arg[i])
	{
		test = cartes_sauvages(arg[i]);
		ret += lencaca(test);
		if (test)
			free_char_char(test);
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
		if (tmp2)
		{
			while (tmp2[i])
			{
				tmp[j] = ft_strdup(tmp2[i]);
				j++;
				i++;
			}
			free_char_char(tmp2);
		}
		index++;
	}
	tmp[j] = NULL;
	return (tmp);
}
