/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_savages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:52:53 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/02 16:36:50 by ghanquer         ###   ########.fr       */
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
	while (arg[j] && (arg[j] == arg[i] || arg[j] == '*'))
	{
		if (arg[j] == '*')
		while (str[i] && ft_strncmp(arg + j, str + i, len_before_star(arg + j)) != 0)
		{
			i++;
			if (str[i] == '\0')
				return (1);
		}
		j++;
	}
	return (0);
}

char	**cartes_sauvages(char *arg)
{
	DIR				*my_dir;
	int				fd[2];
	char			**ret;
	struct dirent	*reading;
	t_name			*fichier;

	reading = NULL;
	ret = NULL;
	fichier = NULL;
	my_dir = opendir(".");
	if (!my_dir)
		return (perror("Wildcards: "), NULL);
	if (!pipe(fd))
		return ("Wildcards: ", NULL);
	fichier = malloc(sizeof(t_name));
	if (!fichier)
		return (NULL);
	while ((reading = readdir(my_dir)) != NULL)
		lst_add(reading->d_name, fichier);
	closedir(my_dir);
	return (ret);
}
