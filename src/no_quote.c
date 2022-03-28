/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:04:52 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/28 18:44:54 by ghanquer         ###   ########.fr       */
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
		if (str[i] && str[i] == '\"')
		{
			nb_quote++;
			while (str[i] != '\"')
				i++;
		}
		i++;
	}
	return (nb_quote);
}

char	**no_quote(char *str)
{
	char	**no_quote_str;
	int		nbquote;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	no_quote_str = NULL;
	no_quote_str = malloc(sizeof(char *) * (how_many_quote(str) + 1));
	if (!no_quote_str)
		return (NULL);
	no_quote_str[i] = "\0";
	return (no_quote_str);
}
