/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/09 10:45:17 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*vireguillemet(char *str, t_info *info)
{
	char	*tmp;
	int		quote;

	if (!ft_strncmp(str, ">>", 2))
	{
		tmp = ft_strtrim(str, " >");
		free(str);
		str = get_del(tmp, info, NULL);
		tmp = ft_strjoin(">>", str);
		free(str);
		return (tmp);
	}
	else if (!ft_strncmp(str, ">", 1))
	{
		tmp = ft_strtrim(str, " >");
		free(str);
		str = get_del(tmp, info, NULL);
		tmp = ft_strjoin(">", str);
		free(str);
		return (tmp);
	}
	else if (!ft_strncmp(str, "<<", 2))
	{
		tmp = ft_strtrim(str, " <");
		quote = asquote(tmp);
		free(str);
		str = get_del(tmp, info, NULL);
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
	else
	{
		tmp = ft_strtrim(str, " <");
		free(str);
		str = get_del(tmp, info, NULL);
		tmp = ft_strjoin("<", str);
		free(str);
		return (tmp);
	}
}

t_arbre	*analyse_syntaxique(char *ligne, t_arbre *arbre, t_info *info)
{
	int	i;
	int	inpar;
	int	insimplegui;
	int	indoublegui;
	int	first_par;
	int	j;
	char *tmp;

	insimplegui = 0;
	indoublegui = 0;
	inpar = 0;
	i = 0;
	if (!ligne)
		return (arbre);
	if (!arbre)
	{
		arbre = malloc(sizeof(t_arbre) * 1);
		arbre->fd = NULL;
		arbre->fg = NULL;
	}
	tmp =  ft_strtrim(ligne, " ");
	if (!ft_strcmp(tmp, ""))
		return (free(ligne), free(tmp), free(arbre), NULL);
	free(tmp);
	while (ligne[i])
	{
		if (!indoublegui && ligne[i] == '\'')
			insimplegui = !insimplegui;
		if (!insimplegui && ligne[i] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[i] == ')')
			inpar--;
		if (!insimplegui && !indoublegui && ligne[i] == '(')
			inpar++;
		if (i && !insimplegui && !indoublegui && !inpar && ((ligne[i] == '&'\
			&& ligne[i - 1] == '&') || (ligne[i] == '|' && ligne[i - 1] == '|')))
		{
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
		i++;
	}
	i = 0;
	inpar = 0;
	insimplegui = 0;
	indoublegui = 0;
	while (ligne[i])
	{
		if (!indoublegui && ligne[i] == '\'')
			insimplegui = !insimplegui;
		if (!insimplegui && ligne[i] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[i] == ')')
			inpar--;
		if (!insimplegui && !indoublegui && ligne[i] == '(')
			inpar++;
		if (!insimplegui && !indoublegui \
				&& !inpar && (ligne[i] == '|' && ligne[i + 1] != '|' \
					&& (!i || ligne[i - 1] != '|')))
		{
			arbre->fd = analyse_syntaxique(ft_substr(ligne, 0, i), arbre->fd, info);
			j = i;
			while (ligne[j])
				j++;
			arbre->fg = analyse_syntaxique(ft_substr(ligne, i + 1, j), arbre->fg, info);
			arbre->commande = ft_strdup("|");
			free(ligne);
			return (arbre);
		}
		i++;
	}
	i = 0;
	inpar = 0;
	insimplegui = 0;
	indoublegui = 0;
	while (ligne[i])
	{
		if (!indoublegui && ligne[i] == '\'')
			insimplegui = !insimplegui;
		if (!insimplegui && ligne[i] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[i] == ')')
			inpar--;
		if (!insimplegui && !indoublegui && ligne[i] == '(')
			inpar++;
		if (!insimplegui && !indoublegui && !inpar && (ligne[i] == '<' || ligne[i] == '>'))
		{
			j = i + 1;
			if (ligne[i + 1] == ligne[i])
				j++;
			while (ligne[j] && ligne[j] == ' ')
				j++;
			insimplegui = 0;
			indoublegui = 0;
			while (ligne[j])
			{
				if (!indoublegui && ligne[j] == '\'')
					insimplegui = !insimplegui;
				if (!insimplegui && ligne[j] == '"')
					indoublegui = !indoublegui;
				if	((!insimplegui && !indoublegui) && (ligne[j] == ' ' || ligne[j] == '>' || ligne[j] == '<' || ligne[j] == '&' || ligne[j] == '|' || ligne[j] == '('))
					break;
				j++;
			}
			while (ligne[j] && ligne[j + 1] && ligne[j + 1] == ' ')
				j++;
			if (ligne[j] && ligne[j + 1] == '(')
			{
				arbre->commande = ft_strdup("");
				free(ligne);
				return (arbre);
			}
			arbre->commande = ft_substr(ligne, i, j - i);
			arbre->commande = vireguillemet(arbre->commande, info);
			arbre->fd = analyse_syntaxique(ft_strjoin_free(ft_substr(ligne, 0, i), ft_substr(ligne, j, ft_strlen(ligne) - j)), arbre->fd, info);
			free(ligne);
			return (arbre);
		}
		i++;
	}
	inpar = 0;
	insimplegui = 0;
	indoublegui = 0;
	i = 0;
	first_par = 0;
	while (ligne[i])
	{
		if (!indoublegui && ligne[i] == '\'')
			insimplegui = !insimplegui;
		if (!insimplegui && ligne[i] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[i] == '(')
		{
			if (!inpar && !first_par)
				first_par = i;
			inpar++;
		}
		if (!insimplegui && !indoublegui && ligne[i] == ')')
			inpar--;
		if (!inpar && !insimplegui && !indoublegui && ligne[i] == ')')
		{
			j = 0;
			while (j != first_par)
			{
				if (ligne[j] != ' ' && ligne[j] != '(')
				{
					arbre->commande = ft_strdup("");
					free(ligne);
					return (arbre);
				}
				j++;
			}
			arbre->fd = analyse_syntaxique(ft_substr(ligne, first_par + 1, i - first_par - 1), arbre->fd, info);
			arbre->commande = ft_strdup("()");
			free(ligne);
			return (arbre);
		}
		i++;
	}
	arbre->commande = ft_strdup(ligne);
	free(ligne);
	return (arbre);
}
