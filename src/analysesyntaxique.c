/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/06 13:02:53 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

/*void	takelogical(char *ligne, t_arbre *arbre, int i)
{
	int	j;
	int	inpar;
	int	indoublegui;
	int	insimplegui;

	insimplegui = 0;
	indoublegui = 0;
	inpar = 0;
	j = i;
	(void)arbre;
	while (j)
	{
		if (!indoublegui && ligne[j] == '\'')
		   insimplegui = !insimplegui;
		if (!insimplegui && ligne[j] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[j] == ')')
			inpar++;
		if (!insimplegui && !indoublegui && ligne[j] == '(')
			inpar--;
		if (j && !indoublegui && !insimplegui && inpar <= 0 \
				&& ((ligne[j] == '|' && ligne[j - 1] == '|') \
					|| (ligne[j] == '&' && ligne[j - 1] == '&')))
		{
			j++;
			break ;
		}
		j--;
	}
	analyse_syntaxique(ft_substr(ligne, j, i - j), arbre);
}

void	takepipe(char *ligne, t_arbre *arbre, int i)
{
	int	j;
	int	inpar;
	int	indoublegui;
	int	insimplegui;

	insimplegui = 0;
	indoublegui = 0;
	inpar = 0;
	j = i;
	(void)arbre;
	while (j)
	{
		if (!indoublegui && ligne[j] == '\'')
		   insimplegui = !insimplegui;
		if (!insimplegui && ligne[j] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[j] == ')')
			inpar++;
		if (!insimplegui && !indoublegui && ligne[j] == '(')
			inpar--;
		if (j && !indoublegui && !insimplegui && !inpar && (ligne[j] == '|' || ligne[j] == '&'))
		{
			j++;
			break ;
		}
		j--;
	}
	analyse_syntaxique(ft_substr(ligne, j, i - j), arbre);
}

void	takefork(char *ligne, t_arbre *arbre, int i)
{
	int	j;
	int	inpar;
	int	indoublegui;
	int	insimplegui;

	insimplegui = 0;
	indoublegui = 0;
	inpar = 0;
	j = i;
	while (j)
	{
		if (!indoublegui && ligne[j] == '\'')
		   insimplegui = !insimplegui;
		if (!insimplegui && ligne[j] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[j] == ')')
			inpar++;
		if (!insimplegui && !indoublegui && ligne[j] == '(')
			inpar--;
		if (j && !inpar && !indoublegui && !insimplegui && !inpar && ligne[j] == '(')
			break ;
		j--;
	}
	if (i)
		analyse_syntaxique(ft_substr(ligne, j + 1, i - j - 1), arbre);
}*/

t_arbre	*analyse_syntaxique(char *ligne, t_arbre *arbre)
{
	int	i;
	int	inpar;
	int	insimplegui;
	int	indoublegui;
	int	first_par;
	int j;

	insimplegui = 0;
	indoublegui = 0;
	inpar = 0;
	i = 0;
	if (!ligne)
		RENVOIE arbre;
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
		if (i && !insimplegui && !indoublegui && !inpar && ((ligne[i] == '&' && ligne[i - 1] == '&') \
			|| (ligne[i] == '|' && ligne[i - 1] == '|')))
		{
			arbre->fg = analyse_syntaxique(ft_substr(ligne, 0, i - 1), arbre->fg);
			j = i;
			while (ligne[j])
				j++;
			arbre->fd = analyse_syntaxique(ft_substr(ligne, i + 1, j), arbre->fd);
			if (ligne[i] == '|')
				arbre->commande = "||";
			if (ligne[i] == '&')
				arbre->commande = "&&";
			return arbre;
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
			arbre->commande = "|";
			return arbre;
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
			if (i && (ligne[i - 1] == '<' || ligne[i - 1] == '>'))
				i--;
			j = i;
			while (ligne[j] && (ligne[j] != '('))
				j++;
			arbre->commande = ft_substr(ligne, i, j - i);
			if (j != i)
				arbre->fg = analyse_syntaxique(ft_substr(ligne, 0, i), arbre->fg);
			i++;
			if (ligne[i] == '<' || ligne[i] == '>')
				i++;
			while (ligne[i] != '<' && ligne[i] != '>' && ligne[i] != '&' && ligne[i] != '|' && ligne[i] != ' ')
				i++;
			while (ligne[j])
				j++;
			arbre->fd = analyse_syntaxique(ft_substr(ligne, i + 1, j - i - 1), arbre->fd);
			return arbre;
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
			arbre->commande = "()";
			return (arbre);
		}
		i++;
	}
	//	printf("%s\n", ligne);
	arbre->commande = ligne;
	return (arbre);
}
