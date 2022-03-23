/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:44:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/23 19:45:13 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MinusculeCoquille.h"

ENTIER	principale(ENTIER ac, CARACTERE **av, CARACTERE **envp)
{
	CARACTERE	*ligne;
	t_info		info;

	info.arbre = (t_arbre *)malloc(TAILLEDE(t_arbre));
	ligne = readline("MinusculeCoquille$>");
	TANTQUE (ligne)
	{
		analyse_syntaxique(ligne, &info);
		free(ligne);
		ligne = readline("MinusculeCoquille$>");
	}
	(VIDE)ac;
	(VIDE)av;
	(VIDE)envp;
	RENVOIE (0);
}

ENTIER	main(ENTIER ac, CARACTERE **av, CARACTERE **envp)
{
	RENVOIE (principale(ac, av, envp));
}
