/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:04:52 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/30 17:41:42 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	how_many_quote(char *str)
{
	int	i;
	int	nb_quote;

	if (!str)
		return (-1);
	i = 0;
	nb_quote = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
		{
			nb_quote++;
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] && str[i] == '"')
		{
			nb_quote++;
			i++;
			while (str[i] != '"')
				i++;
		}
		i++;
	}
	printf("nb_quote : %d\n", nb_quote);
	return (nb_quote);
}

int	size_of_no_quote(char *str, int j)
{
	int	i;

	i = 0;
	if (str[j] && str[j] != '"' && str[j] != '\'')
	{
		while (str[j] && str[j] != '"' && str[j] != '\'')
		{
			j++;
			i++;
		}
	}
	else if (str[j] == '"')
	{
		j++;
		while (str[j] != '"')
		{
			j++;
			i++;
		}
	}
	else if (str[j] == '\'')
	{
		j++;
		while (str[j] != '\'')
		{
			j++;
			i++;
		}
	}
	printf("ligne = %d\n", i);
	return (i);
}

void	get_every_line(char *str, char **no_quote_str)
{
	int	i;
	int	j;
	int	k;

	if (!*str)
		return ;
	j = 0;
	i = 0;
	while (str[i])
	{
		printf("Passage %d\n", j + 1);
		k = 0;
		no_quote_str[j] = malloc(sizeof(char) * size_of_no_quote(str, i) + 1);
		if (!no_quote_str[j])
			return ;
		no_quote_str[j][size_of_no_quote(str, i)] = '\0';
		if(str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				no_quote_str[j][k] = str[i];
				k++;
				i++;
			}
			i++;
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
			{
				no_quote_str[j][k] = str[i];
				k++;
				i++;
			}
			i++;
		}
		else
		{
			while (str[i] && str[i] != '\'' && str[i] != '"')
			{
				no_quote_str[j][k] = str[i];
				k++;
				i++;
			}
		}
		j++;
	}
	no_quote_str[how_many_quote(str) + 1] = "\0";
}

char	**no_quote(char *str)
{
	char	**no_quote_str;

	if (!str)
		return (NULL);
	if (how_many_quote(str) == 0)
		return (ft_split(str, ' '));
	no_quote_str = NULL;
	no_quote_str = malloc(sizeof(char *) * (how_many_quote(str) + 2));
	if (!no_quote_str)
		return (NULL);
	no_quote_str[how_many_quote(str)] = NULL;
	get_every_line(str, no_quote_str);
	return (no_quote_str);
}
