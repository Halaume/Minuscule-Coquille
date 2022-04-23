/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/23 19:27:07 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

t_arbre	*analyse_syntaxique(char *ligne, t_arbre *arbre)
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
	if (!strcmp(tmp, ""))
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
			arbre->fd = analyse_syntaxique(ft_substr(ligne, 0, i - 1), arbre->fd);
			j = i;
			while (ligne[j])
				j++;
			arbre->fg = analyse_syntaxique(ft_substr(ligne, i + 1, j), arbre->fg);
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
			arbre->fd = analyse_syntaxique(ft_substr(ligne, 0, i), arbre->fd);
			j = i;
			while (ligne[j])
				j++;
			arbre->fg = analyse_syntaxique(ft_substr(ligne, i + 1, j), arbre->fg);
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
			arbre->fd = analyse_syntaxique(ft_strjoin_free(ft_substr(ligne, 0, i), ft_substr(ligne, j, ft_strlen(ligne) - j)), arbre->fd);
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
			arbre->fd = analyse_syntaxique(ft_substr(ligne, first_par + 1, i - first_par - 1), arbre->fd);
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
