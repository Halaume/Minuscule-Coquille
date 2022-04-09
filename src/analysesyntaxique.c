/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/09 14:26:42 by tnaton           ###   ########.fr       */
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
			arbre->fg = analyse_syntaxique(ft_substr(ligne, 0, i - 1), arbre->fg);
			j = i;
			while (ligne[j])
				j++;
			arbre->fd = analyse_syntaxique(ft_substr(ligne, i + 1, j), arbre->fd);
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
		if (i && i < (int)ft_strlen(ligne) && !insimplegui && !indoublegui \
				&& !inpar && (ligne[i] == '|' && ligne[i + 1] != '|' \
					&& ligne[i - 1] != '|'))
		{
			arbre->fg = analyse_syntaxique(ft_substr(ligne, 0, i), arbre->fg);
			j = i;
			while (ligne[j])
				j++;
			arbre->fd = analyse_syntaxique(ft_substr(ligne, i + 1, j), arbre->fd);
			arbre->commande = ft_strdup("|");
			free(ligne);
			return (arbre);
		}
		i++;
	}
	inpar = 0;
	insimplegui = 0;
	indoublegui = 0;
	while (i)
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
			if (i && (ligne[i - 1] == '<' || ligne[i - 1] == '>'))
				i--;
			while (ligne[j] && ligne[j] == ' ')
				j++;
			while (ligne[j] && ligne[j] != ' ' && ligne[j] != '>' && ligne[j] != '<' && ligne[j] != '&' && ligne[j] != '|')
				j++;
			arbre->commande = ft_substr(ligne, i, j - i);
			arbre->fd = analyse_syntaxique(ft_strjoin(ft_substr(ligne, 0, i), ft_substr(ligne, j, ft_strlen(ligne) - j)), arbre->fd);
			free(ligne);
			return (arbre);
		}
		i--;
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
