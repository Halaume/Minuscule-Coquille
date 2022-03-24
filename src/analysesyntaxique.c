/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/24 12:03:02 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

VIDE	analyse_syntaxique(CARACTERE *ligne, t_info *info)
{
	ENTIER	i;

	i = 0;
	SI (!ligne)
		RENVOIE ;
	(VIDE)i;
	(VIDE)info;
	/*	TANTQUE (ligne[i])
	{
		SI (i && (ligne[i] == '&' && ligne[i - 1]) || (ligne[i] == '|' \
					&& ligne[i - 1] == '|'))
			logique(ligne, info);
		SINON SI (ligne[i] == '|')
			tuyau(ligne, info);
		SINON SI (ligne[i] == '('

	}*/
}
