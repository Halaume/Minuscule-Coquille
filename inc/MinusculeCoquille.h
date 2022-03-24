/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MinusculeCoquille.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:09:23 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/24 12:29:27 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINUSCULECOQUILLE_H
# define MINUSCULECOQUILLE_H

# include "France.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef STRUCTURE s_arbre
{
	CARACTERE			*commande;
	STRUCTURE s_arbre	**logique;
	STRUCTURE s_arbre	**tuyau;
	STRUCTURE s_arbre	*fourchette;
	STRUCTURE s_arbre	**argument;
}	t_arbre;

typedef STRUCTURE s_info
{
	t_arbre	*arbre;
}	t_info;

VIDE	analyse_syntaxique(CARACTERE *ligne, t_info *info);

#endif
