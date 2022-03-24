/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/24 17:48:52 by tnaton           ###   ########.fr       */
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
	if (ligne[end + 1])
		end++;
	while (ligne[end] && ((ligne[end] != '|' && ligne[end] != '&') || (inpar || ingui)))
	{
		if (!ingui && ligne[end] == '(')
			inpar = 1;
		if (!ingui && ligne[end] == ')')
			inpar = 0;
		if (!inpar && (ligne[end] == '\'' || ligne[end] == '"'))
			ingui = !ingui;
		end++;
	}
	if (ligne[end])
		end++;
	printf("%s\n", ft_substr(ligne, start, (end - start)));
}

void	getpar(char *ligne, t_arbre *arbre, int start)
{
	int	end;

	(void)arbre;
	end = start;
	while (ligne[end] != ')')
		end++;
	printf("%s\n", ft_substr(ligne, start, (end - start + 1)));
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
	while (ligne[i])
	{
		if (!dansparenthese && (ligne[i] == '\'' || ligne[i] == '"'))
			dansguillemet = !dansguillemet;
		if (i && !dansguillemet && !dansparenthese && ((ligne[i] == '&' && ligne[i - 1] == '&') \
					|| (ligne[i] == '|' && ligne[i - 1] == '|')))
			prendpart(ligne, arbre, i);
		else if (!dansguillemet && !dansparenthese && ligne[i] == '|' && ligne[i + 1] != '|')
			prendpart(ligne, arbre, i);
		else if (!dansguillemet && ligne[i] == '(')
		{
			dansparenthese = 1;
			getpar(ligne, arbre, i);
		}
		else if (!dansguillemet && ligne[i] == ')')
			dansparenthese = 0;
		i++;
	}
}
