/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartes_savages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:52:53 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/04 18:39:22 by ghanquer         ###   ########.fr       */
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
	while (arg[j] && arg[i] && (arg[j] == arg[i] || arg[j] == '*'))
	{
		if (arg[j] == '*')
		{
			if (arg[j + 1] == '\0')
				return (0);
			while (str[i] && ft_strncmp(arg + j + 1, str + i, len_before_star(arg + j + 1)) != 0)
			{
				i++;
				if (str[i] == '\0' && arg[j + len_before_star(arg + j + 1)] != '\0')
					return (1);
			}
		}
		j++;
	}
	return (0);
}

int	nb_of_good_word(char *arg, t_name *name)
{
	int		i;
	t_name	*tmp;

	tmp = name;
	i= 0;
	while (tmp)
	{
		if (is_good_word(arg, tmp->name) == 0)
			i++;
		tmp = tmp->next;
	}
	return (0);
}

char	**cartes_sauvages(char *arg)
{
	DIR				*my_dir;
	char			**ret;
	struct dirent	*reading;
	t_name			*fichier;
	t_name			*tmp;
	int				nb_word;
	int				i;

	reading = NULL;
	ret = NULL;
	fichier = NULL;
	i = 0;
	my_dir = opendir(".");
	if (!my_dir)
		return (perror("Wildcards: "), NULL);
	while ((reading = readdir(my_dir)) != NULL)
		lst_add(&fichier, new_lst(ft_strdup(reading->d_name)));
	nb_word = nb_of_good_word(arg, fichier);
	printf("nb of good_word = %d\n", nb_word);
	ret = malloc(sizeof(char *) * (nb_word + 1));
	if (!ret)
		return (NULL);
	ret[nb_of_good_word(arg, fichier)] = "\0";
	tmp = fichier;
	while (tmp && i < nb_word)
	{
		if (is_good_word(arg, tmp->name) == 0)
		{
			printf("HERE\n");
			ret[i] = ft_strdup(tmp->name);
			i++;
		}
		tmp = tmp->next;
	}
	if (i < nb_word - 1)
		printf("Counting error\n");
	free_name(fichier);
	closedir(my_dir);
	i = 0;
	while (strncmp(ret[i], "\0", 1))
	{
		printf("%s\n", ret[i]);
		i++;
	}
	return (ret);
}

int	main(int argc, char **argv)
{
	(void)argc;
	char **test = cartes_sauvages(argv[1]);
	int i;
	i = 0;
	while (strncmp(test[i], "\0", 1))
	{
		printf("%s\n", test[i]);
		i++;
	}
	free(test);
	return (0);
}
