/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:39:56 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 15:40:22 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*vireguillemet(char *str, t_info *info)
{
	if (!ft_strncmp(str, ">>", 2))
		return (vireconcat(str, info));
	else if (!ft_strncmp(str, ">", 1))
		return (vireout(str, info));
	else if (!ft_strncmp(str, "<<", 2))
		return (virehere(str, info));
	else if (!ft_strncmp(str, "<", 1))
		return (virein(str, info));
	return (str);
}

char	*aled(char *str, t_info *info)
{
	char	*tmp;
	int		quote;
	int		asex;

	if (!ft_strncmp(str, "<<", 2) && ft_strlen(str) > 2)
	{
		tmp = ft_strtrim(str, " <");
		quote = asquote(tmp);
		free(str);
		str = get_del(tmp, info, &asex, 1);
		if (!ft_strlen(str) && asex)
			return (free(str), NULL);
		tmp = ft_strjoin("<<", str);
		if (quote)
		{
			free(str);
			str = ft_strjoin("\"", tmp);
			free(tmp);
			tmp = ft_strjoin(str, "\"");
		}
		free(str);
		return (tmp);
	}
	return (str);
}

void	gui(char c, int *dg, int *sg, int *p)
{
	if (!*dg && c == '\'')
		*sg = !*sg;
	else if (!*sg && c == '"')
		*dg = !*dg;
	else if (!*sg && !*dg && c == ')')
		(*p)--;
	else if (!*sg && !*dg && c == '(')
		(*p)++;
}

t_arbre	*etou(t_arbre *arbre, char *ligne, t_info *info, int i)
{
	int	j;

	arbre->fd = analyse_syntaxique(ft_substr(ligne, 0, i - 1), arbre->fd, info);
	j = i;
	while (ligne[j])
		j++;
	arbre->fg = analyse_syntaxique(ft_substr(ligne, i + 1, j), arbre->fg, info);
	if (ligne[i] == '|')
		arbre->commande = ft_strdup("||");
	if (ligne[i] == '&')
		arbre->commande = ft_strdup("&&");
	free(ligne);
	return (arbre);
}

t_arbre	*pipou(t_arbre *arbre, char *ligne, t_info *info, int i)
{
	int	j;

	arbre->fd = analyse_syntaxique(ft_substr(ligne, 0, i), arbre->fd, \
			info);
	j = i;
	while (ligne[j])
		j++;
	arbre->fg = analyse_syntaxique(ft_substr(ligne, i + 1, j), \
	arbre->fg, info);
	arbre->commande = ft_strdup("|");
	free(ligne);
	return (arbre);
}
