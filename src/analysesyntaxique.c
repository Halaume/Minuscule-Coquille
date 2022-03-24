/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/24 17:45:50 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

VIDE	analyse_syntaxique(CARACTERE *ligne, t_info *info)
{
	ENTIER	i;
//	ENTIER	dansguillemet;

//	dansguillemet = 0;
	i = 0;
	SI (!ligne)
		RENVOIE ;
	(VIDE)i;
	(VIDE)info;
/*	TANTQUE (ligne[i])
	{
		SI (ligne[i] == '\'' || ligne[i] == '"')
			dansguillemet = !dansguillemet;
		SI (i && !dansguillemet && ((ligne[i] == '&' && ligne[i - 1] == '&') \
					|| (ligne[i] == '|' && ligne[i - 1] == '|')))
			logique(ligne, info, i);
		SINON SI (!dansguillemet && ligne[i] == '|')
			tuyau(ligne, info, i);
		SINON SI (!dansguillemet && ligne[i] == '(')
			fourchette(ligne, info, i);
	}*/
}
