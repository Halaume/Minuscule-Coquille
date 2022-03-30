/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:44:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/30 14:36:54 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	verifieligne(char *ligne)
{
	int	i;
	int	parenthese;
	int	doubleguillemet;
	int	simpleguillemet;

	parenthese = 0;
	i = 0;
	doubleguillemet = 0;
	simpleguillemet = 0;
	while (ligne[i])
	{
		if (ligne[i] == '"' && !simpleguillemet)
			doubleguillemet = !doubleguillemet;
		else if (ligne[i] == '\'' && !doubleguillemet)
			simpleguillemet = !simpleguillemet;
		else if (ligne[i] == '(' && !simpleguillemet && !doubleguillemet) 
			parenthese++;
		else if (ligne[i] == ')' && !simpleguillemet && !doubleguillemet)
			parenthese--;
		if (parenthese < 0)
			return (1);
		i++;
	}
	if (parenthese != 0 || simpleguillemet != 0 || doubleguillemet != 0)
		return (1);
	return (0);
}

void	print_arbre(t_arbre *arbre, int type)
{
	if (arbre && arbre->commande)
	{
		if (type == 0)
			printf("root :");
		if (type == 1)
			printf("fg :");
		if (type == 2)
			printf("fd :");
		printf("%s\n", arbre->commande);
		print_arbre(arbre->fd, 2);
		print_arbre(arbre->fg, 1);
	}
}

int	principale(int ac, char **av, char **envp)
{
	char	*ligne;
	t_info		info;

	info.arbre = (t_arbre *)malloc(TAILLEDE(t_arbre));
	ligne = readline("MinusculeCoquille$>");
	while (ligne)
	{
		info.arbre->fd = NULL;
		info.arbre->fg = NULL;
		if (verifieligne(ligne))
			printf("Erreur syntaxique\n");
		else
		{
			analyse_syntaxique(ligne, info.arbre);
			print_arbre(info.arbre, 0);
		}
		if (ft_strlen(ligne))
			add_history(ligne);
		free(ligne);
		ligne = readline("MinusculeCoquille$>");
	}
	(void)ac;
	(void)av;
	(void)envp;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	return (principale(ac, av, envp));
}
