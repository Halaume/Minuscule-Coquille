/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:04:52 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/29 19:05:53 by ghanquer         ###   ########.fr       */
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
			while (str[i] != '\'')
				i++;
		}
		if (str[i] && str[i] == '"')
		{
			nb_quote++;
			while (str[i] != '"')
				i++;
		}
		i++;
	}
	return (nb_quote);
}

void	**get_every_line(char *str, char **no_quote_str)
{
	int	i;
	int	j;
	int	k;

	if (!str)
		return (NULL);
	i = 0;
	while (j < how_many_quote(str) && str[i])
	{
		k = 0;
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i] != ' ')
		{
			no_quote_str[j][k] = str[i];
			k++;
			i++;
		}
		j++;
		k = 0;
		if(str[i] == '\'')
		{
			while (str[i] && str[i] != '\'')
			{
				no_quote_str[j][k] = str[i];
				i++;
			}
			i++;
			j++;
		}
		else if (str[i] == '"')
		{
			while (str[i] && str[i] != '"')
			{
				no_quote_str[j][k] = str[i];
				i++;
			}
			i++;
			j++;
		}
	}
	no_quote_str[how_many_quote(str) + 1] = "\0";
}

char	**no_quote(char *str)
{
	char	**no_quote_str;
	int		nbquote;

	if (!str)
		return (NULL);
	no_quote_str = NULL;
	no_quote_str = malloc(sizeof(char *) * (how_many_quote(str) + 1));
	if (!no_quote_str)
		return (NULL);
	get_every_line(str, no_quote_str);
	return (no_quote_str);
}
