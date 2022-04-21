/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:04:52 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/21 12:52:32 by ghanquer         ###   ########.fr       */
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
			while (str[i] && str[i] == '\'')
				i++;
		}
		if (str[i] && str[i] == '"')
		{
			nb_quote++;
			i++;
			while (str[i] && str[i] == '"')
				i++;
		}
		if (str[i])
			i++;
	}
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
	return (i);
}

void	get_every_line(char *str, char **no_quote_str)
{
	int	i;
	int	j;
	int	k;
	int	is_dquote;
	int	is_quote;

	if (!*str)
		return ;
	j = 0;
	i = 0;
	is_quote = 0;
	is_dquote = 0;
	while (str[i])
	{
		k = 0;
		no_quote_str[j] = malloc(sizeof(char) * size_of_no_quote(str, i) + 1);
		if (!no_quote_str[j])
			return ;
		no_quote_str[j][size_of_no_quote(str, i)] = '\0';
		if (str[i] == '\'')
		{
			is_quote = 1;
			i++;
			while (str[i] && str[i] == '\'')
				i++;
		}
		else if (str[i] == '"')
		{
			is_dquote = 1;
			i++;
			while (str[i] && str[i] == '"')
				i++;
		}
		if (is_quote == 1)
		{
			while (str[i] && str[i] != '\'')
			{
				no_quote_str[j][k] = str[i];
				k++;
				i++;
			}
			is_quote = 0;
			j++;
		}
		else if (is_dquote == 1)
		{
			while (str[i] && str[i] != '"')
			{
				no_quote_str[j][k] = str[i];
				k++;
				i++;
			}
			is_dquote = 0;
			j++;
		}
		else
		{
			while (str[i] && str[i] != '"' && str[i] != '\'')
			{
				no_quote_str[j][k] = str[i];
				k++;
				i++;
			}
			j++;
		}
	}
}

char	*no_quote(char *str)
{
	char	**no_quote_str;
	char	*joined_str;
	int		i;
	int		nb_word;

	nb_word = how_many_quote(str);
	joined_str = "\0";
	if (!str)
		return (NULL);
	if (nb_word == 0)
		return (str);
	no_quote_str = NULL;
	no_quote_str = malloc(sizeof(char *) * (nb_word + 2));
	if (!no_quote_str)
		return (NULL);
	no_quote_str[nb_word + 1] = NULL;
	get_every_line(str, no_quote_str);
	i = 0;
	if (!no_quote_str)
		return (NULL);
	while (no_quote_str[i])
	{
		joined_str = ft_strjoin(joined_str, no_quote_str[i]);
		i++;
	}
	free_char_char(no_quote_str);
	return (joined_str);
}

char	**no_quote_tab(char *str)
{
	char	**no_quote_str;
	char	*joined_str;
	int		i;
	int		nb_word;

	nb_word = how_many_quote(str);
	joined_str = "\0";
	if (!str)
		return (NULL);
	no_quote_str = NULL;
	no_quote_str = malloc(sizeof(char *) * (nb_word + 2));
	if (!no_quote_str)
		return (NULL);
	no_quote_str[nb_word + 1] = NULL;
	get_every_line(str, no_quote_str);
	i = 0;
	if (!no_quote_str)
		return (NULL);
	while (no_quote_str[i])
	{
		printf("str = %s\n", no_quote_str[i]);
		i++;
	}
	return (no_quote_str);
}
