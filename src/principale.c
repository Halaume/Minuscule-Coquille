/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:44:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/24 14:55:09 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

ENTIER	verifieligne(CARACTERE *ligne)
{
	ENTIER	i;
	ENTIER	parenthese;
	ENTIER	doubleguillemet;
	ENTIER	simpleguillemet;
	parenthese = 0;
	i = 0;
	doubleguillemet = 0;
	simpleguillemet = 0;
	TANTQUE (ligne[i])
	{
		if (ligne[i] == '"' && !simpleguillemet && !parenthese)
			doubleguillemet = !doubleguillemet;
		SINON SI (ligne[i] == '\'' && !doubleguillemet && !parenthese)
			simpleguillemet = !simpleguillemet;
		SINON SI (ligne[i] == '(' && !simpleguillemet && !doubleguillemet) 
			parenthese++;
		SINON SI (ligne[i] == ')' && !simpleguillemet && !doubleguillemet)
			parenthese--;
		SI (parenthese < 0)
			RENVOIE (1);
		i++;
	}
	SI (parenthese != 0 || simpleguillemet != 0 || doubleguillemet != 0)
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
