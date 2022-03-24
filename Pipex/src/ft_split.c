/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:27:03 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/18 16:21:11 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	**free_tab(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	nb_word(char const *s, char c)
{
	int	count;
	int	i;

	if (!s[0])
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			while (s[i] != c && s[i])
				i++;
			count++;
		}
	}
	return (count);
}

static void	ft_get_next_str(char **next_str, unsigned int *next_len, char c)
{
	unsigned int	i;

	*next_str += *next_len;
	*next_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*next_len)++;
		i++;
	}
}

char	**ft_split(char *s, char c)
{
	char				**tab;
	char				*next_str;
	unsigned int		nbword;
	unsigned int		next_len;
	unsigned int		i;

	i = 0;
	nbword = nb_word(s, c);
	next_str = (char *) s;
	next_len = 0;
	tab = malloc(sizeof(char *) * (nbword + 1));
	if (!tab)
		return (NULL);
	while (i < nbword)
	{
		ft_get_next_str(&next_str, &next_len, c);
		if (!next_len)
			return (tab);
		tab[i] = malloc(sizeof(char) * next_len + 1);
		if (!tab[i])
			return (free_tab(tab));
		ft_strlcpy(tab[i++], next_str, next_len + 1);
	}
	tab[i] = NULL;
	return (tab);
}
