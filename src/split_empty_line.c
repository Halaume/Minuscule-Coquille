/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_empty_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:10:03 by ghanquer          #+#    #+#             */
/*   Updated: 2022/04/22 14:22:57 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

static unsigned int	count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;
	int		is_in_quote;

	i = 0;
	count = 0;
	if (!s || !*s)
		return (-1);
	while (s[i])
	{
		is_in_quote = 0;
		if (s[i] == '\'')
			is_in_quote = 1;
		else if (s[i] == '"')
			is_in_quote = 2;
		while (s[i] && s[i] == c && is_in_quote <= 0)
		{
			if (s[i] == '\'')
			{
				i++;
				is_in_quote = 1;
				while (s[i] == '\'')
				{
					is_in_quote *= -1;
					i++;
				}
			}
			else if (s[i] == '"')
			{
				i++;
				is_in_quote = 2;
				while (s[i] == '"')
				{
					is_in_quote *= -1;
					i++;
				}
			}
			else
				i++;
		}
		printf("%d\n", is_in_quote);
		if (s[i] && s[i] != c)
			count++;
		if (is_in_quote == 1)
		{
			if (s[i] != '\'')
				while (s[i] && s[i] != '\'')
					i++;
			else
				i++;
		}
		else if (is_in_quote == 2)
			while (s[i] && s[i] != '"')
				i++;
		else
			while (s[i] && s[i] != c)
				i++;
	}
	return (count + 1);
}

static void	ft_free(char **list, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(list[i++]);
	free(list);
}

char	**split_empty_line(char *s, char c)
{
	char	**dest;
	size_t	i;
	size_t	start;
	size_t	end;
	int		is_in_quote;

	i = 0;
	end = 0;
	if (!s)
		return (NULL);
	dest = NULL;
	dest = (char **)ft_calloc(sizeof(char *), count_word(s, c));
	printf("nb mots = %d\n", count_word(s, c));
	if (!dest)
		return (NULL);
	while ((i + 1) < count_word(s, c))
	{
		is_in_quote = 0;
		if (s[end] == '\'')
			is_in_quote = 1;
		else if (s[end] == '"')
			is_in_quote = 2;
		while (s[end] && s[end] == c && is_in_quote <= 0)
		{
			if (s[end] == '\'')
			{
				end++;
				is_in_quote = 1;
				while (s[end] == '\'')
				{
					is_in_quote *= -1;
					end++;
				}
			}
			else if (s[end] == '"')
			{
				end++;
				is_in_quote = 2;
				while (s[end] == '"')
				{
					is_in_quote *= -1;
					end++;
				}
			}
			else
				end++;
		}
		start = end;
		if (is_in_quote == 1)
			while (s[end] && s[end] != '\'')
				end++;
		else if (is_in_quote == 2)
			while (s[end] && s[end] != '"')
				end++;
		else
			while (s[end] && s[end] != c)
				end++;
		dest[i++] = ft_substr(s, start, (end - start));
		if (!dest[i - 1])
		{
			ft_free(dest, (i - 1));
			return (NULL);
		}
	}
	return (dest);
}
