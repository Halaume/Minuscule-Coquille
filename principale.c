/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:44:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/24 11:23:27 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MinusculeCoquille.h"

ENTIER	verifieligne(CARACTERE *ligne)
{
	ENTIER	i;
	ENTIER	parenthèse;
	ENTIER	doubleguillemet;
	ENTIER	simpleguillemet;
	parenthèse = 0;
	i = 0;
	doubleguillemet = 0;
	simpleguillemet = 0;
	TANTQUE (ligne[i])
	{
		SI (ligne[i] == '"' && !simpleguillemet && !parenthèse)
			doubleguillemet = !doubleguillemet;
		SI (ligne[i] == '\'' && !doubleguillemet && !parenthèse)
			simpleguillemet = !simpleguillemet;
		SI (ligne[i] == '(')
			parenthèse++;
		SINON SI (ligne[i] == ')')
			parenthèse--;
		SI (parenthèse < 0)
			RENVOIE (1);
		i++;
	}
	SI (parenthèse != 0 || simpleguillemet != 0 || doubleguillemet != 0)
		RENVOIE (1);
	SI (ligne[i - 1] == ';' || ligne[i - 1] == '\\')
		RENVOIE (1);
	RENVOIE (0);
}

ENTIER	principale(ENTIER ac, CARACTERE **av, CARACTERE **envp)
{
	CARACTERE	*ligne;
	t_info		info;

	info.arbre = (t_arbre *)malloc(TAILLEDE(t_arbre));
	ligne = readline("MinusculeCoquille$>");
	TANTQUE (ligne)
	{
		SI (verifieligne(ligne))
			printf("Erreur syntaxique\n");
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
