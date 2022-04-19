/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:44:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/09 15:30:54 by tnaton           ###   ########.fr       */
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

void	padding(char ch, int n)
{
	int	i;

	for (i = 0; i < n; i++)
		putchar(ch);
}

void	structure(t_arbre *root, int level)
{
	if (root == NULL)
		padding(' ', level);
	else
	{
		structure(root->fd, level + 1);
		padding('	', level);
		printf(">%s<\n", root->commande);
		structure (root->fg, level + 1);
	}
}

void	freearbre(t_arbre *arbre)
{
	if (arbre->fd)
		freearbre(arbre->fd);
	if (arbre->fg)
		freearbre(arbre->fg);
	free(arbre->commande);
	free(arbre);
}

int	checkarbre(t_arbre *arbre)
{
	char *tmp;

	if (arbre)
	{
		if (!strcmp(arbre->commande, "()") || !strcmp(arbre->commande, "|") || !strcmp(arbre->commande, "&&") || !strcmp(arbre->commande, "||"))
		{
			if (arbre->fd)// && (!strcmp(arbre->fd->commande, "") || !strcmp(ft_strtrim(arbre->fd->commande, " "), "")))
			{
				tmp = ft_strtrim(arbre->fd->commande, " ");
				if (!strcmp(tmp, ""))
					return (free(tmp), 1);
				free(tmp);
			}
			if (arbre->fg)// && (!strcmp(arbre->fg->commande, "") || !strcmp(ft_strtrim(arbre->fg->commande, " "), "")))
			{
				tmp = ft_strtrim(arbre->fg->commande, " ");
				if (!strcmp(tmp, ""))
					return (free(tmp), 1);
				free(tmp);
			}
		}
	}
	if (arbre->fd && arbre->fg)
		return (checkarbre(arbre->fd) + checkarbre(arbre->fg));
	else if (arbre->fg)
		return (checkarbre(arbre->fg));
	else if (arbre->fd)
		return (checkarbre(arbre->fd));
	return (0);
}

int	principale(int ac, char **av, char **envp)
{
	char	*ligne;
	t_info	info;

	ligne = readline("MinusculeCoquille$>");
	while (ligne && strcmp(ligne, "exit"))
	{
		if (ft_strlen(ligne))
			add_history(ligne);
		info.arbre = NULL;
		if (verifieligne(ligne))
		{
			printf("Erreur syntaxique\n");
			free(ligne);
		}
		else
		{
			info.arbre = analyse_syntaxique(ligne, info.arbre);
			if (!checkarbre(info.arbre))
			{
				structure(info.arbre, 0);
				printf("\n");
			}
			else
				printf("Erreur syntaxique\n");
		}
		if (info.arbre)
			freearbre(info.arbre);
		ligne = readline("MinusculeCoquille$>");
	}
	free(ligne);
	(void)ac;
	(void)av;
	(void)envp;
	rl_clear_history();
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	return (principale(ac, av, envp));
}
