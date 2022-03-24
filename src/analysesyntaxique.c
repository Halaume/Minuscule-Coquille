/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/24 20:05:58 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

void	prendpart(char *ligne, t_arbre *arbre, int start)
{
	int	end;
	int	inpar;
	int	ingui;

	inpar = 0;
	ingui = 0;
	(void)arbre;
	end = start;
	if (ligne[end] == '(')
		inpar++;
	if (ligne[end + 1])
		end++;
	while (ligne[end] && ((ligne[end] != '|' && ligne[end] != '&') || (inpar || ingui)))
	{
		if (!ingui && ligne[end] == '(')
			inpar++;
		if (!ingui && ligne[end] == ')')
			inpar--;
		if (ligne[end] == '\'' || ligne[end] == '"')
			ingui = !ingui;
		end++;
	}
	if (ligne[end])
		end++;
	printf("prendpart : %s\n", ft_substr(ligne, start, (end - start)));
}

void	getpar(char *ligne, t_arbre *arbre, int start)
{
	int	end;
	int	inpar;
	int	ingui;

	ingui = 0;
	inpar = 1;
	(void)arbre;
	end = start + 1;
	while (inpar != 0)
	{
		if (ligne[end] == '\'')
			ingui = !ingui;
		if (ligne[end] == '"')
			ingui = !ingui;
		if (!ingui && ligne[end] == '(')
			inpar++;
		if (!ingui && ligne[end] == ')')
			inpar--;
		end++;
	}
	printf("getpar : %s\n", ft_substr(ligne, start, (end - start + 1)));
}


void	analyse_syntaxique(char *ligne, t_arbre *arbre)
{
	int	i;
	int	dansparenthese;
	int	dansguillemet;

	dansguillemet = 0;
	dansparenthese = 0;
	i = 0;
	if (!ligne)
		RENVOIE ;
	prendpart(ligne, arbre, 0);
	while (ligne[i])
	{
		if (ligne[i] == '\'' || ligne[i] == '"')
			dansguillemet = !dansguillemet;
		if (i && !dansguillemet && !dansparenthese && ((ligne[i] == '&' && ligne[i - 1] == '&') \
					|| (ligne[i] == '|' && ligne[i - 1] == '|')))
			prendpart(ligne, arbre, i);
		else if (!dansguillemet && !dansparenthese && ligne[i] == '|' && ligne[i + 1] != '|')
			prendpart(ligne, arbre, i);
		else if (!dansguillemet && ligne[i] == '(')
		{
			dansparenthese++;
			getpar(ligne, arbre, i);
		}
		else if (!dansguillemet && ligne[i] == ')')
			dansparenthese--;
		i++;
	}
}
