/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principale2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:04:31 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 16:14:43 by tnaton           ###   ########.fr       */
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
		gui(ligne[i], &doubleguillemet, &simpleguillemet, &parenthese);
		if (parenthese < 0)
			return (1);
		i++;
	}
	if (parenthese != 0 || simpleguillemet != 0 || doubleguillemet != 0)
		return (1);
	return (0);
}

void	freearbrecmd(t_arbre *arbre)
{
	char	*tmp;

	tmp = ft_strtrim(arbre->commande, "\"<");
	if (!ft_strncmp(tmp, "/tmp/.", 6))
		unlink(tmp);
	free(tmp);
	tmp = NULL;
	free(arbre->commande);
	arbre->commande = NULL;
}

void	freearbre(t_arbre *arbre)
{
	if (arbre)
	{
		if (arbre->fd)
		{
			freearbre(arbre->fd);
			arbre->fd = NULL;
		}
		if (arbre->fg)
		{
			freearbre(arbre->fg);
			arbre->fg = NULL;
		}
		if (arbre->commande)
			freearbrecmd(arbre);
		if (arbre)
		{
			free(arbre);
			arbre = NULL;
		}
	}
}

int	ischiant(t_arbre *arbre)
{
	return (!ft_strcmp(arbre->commande, "()") || \
			!ft_strcmp(arbre->commande, "|") \
		|| !ft_strcmp(arbre->commande, "&&") || \
		!ft_strcmp(arbre->commande, "||"));
}

int	istropchiant(char *tmp)
{
	return (!ft_strcmp(tmp, "") || !ft_strcmp(tmp, ">") || \
			!ft_strcmp(tmp, ">>") || !ft_strcmp(tmp, "<") || \
			!ft_strcmp(tmp, "<<"));
}
