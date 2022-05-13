/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:36:05 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/13 12:51:29 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

t_arbre	*ft_redir(t_arbre *arbre, char *ligne, t_info *info, int *lst)
{
	int	indoublegui;
	int	insimplegui;
	int	inpar;

	indoublegui = 0;
	insimplegui = 0;
	inpar = 0;
	lst[1] = 0;
	while (ligne[lst[1]])
	{
		gui(ligne[lst[1]], &indoublegui, &insimplegui, &inpar);
		if (!insimplegui && !indoublegui && !inpar && (ligne[lst[1]] == '<' || \
					ligne[lst[1]] == '>'))
			return (redir(arbre, ligne, info, lst[1]));
		lst[1]++;
	}
	return (NULL);
}

t_arbre	*ft_par(t_arbre *arbre, char *ligne, t_info *info, int *lst)
{
	int	indoublegui;
	int	insimplegui;
	int	inpar;

	indoublegui = 0;
	insimplegui = 0;
	inpar = 0;
	lst[0] = 0;
	lst[1] = 0;
	while (ligne[lst[1]])
	{
		gui(ligne[lst[1]], &indoublegui, &insimplegui, &inpar);
		if (!(inpar - 1) && !lst[0] && !insimplegui && !indoublegui \
				&& ligne[lst[1]] == '(')
			lst[0] = lst[1];
		if (!inpar && !insimplegui && !indoublegui && ligne[lst[1]] == ')')
			return (par(arbre, ligne, info, lst));
		lst[1]++;
	}
	return (NULL);
}

t_arbre	*initarbre(t_arbre *arbre, char *ligne)
{
	char	*tmp;

	if (!ligne)
		return (arbre);
	if (!arbre)
	{
		arbre = malloc(sizeof(t_arbre) * 1);
		arbre->fd = NULL;
		arbre->fg = NULL;
	}
	tmp = ft_strtrim(ligne, " ");
	if (!ft_strcmp(tmp, ""))
		return (free(ligne), free(tmp), free(arbre), NULL);
	free(tmp);
	return (arbre);
}

t_arbre	*lanceanal(t_arbre *arbre, char *ligne, t_info *info, int *lst)
{
	t_arbre	*tmp;

	tmp = ft_etou(arbre, ligne, info, lst);
	if (tmp)
		return (tmp);
	tmp = ft_pipou(arbre, ligne, info, lst);
	if (tmp)
		return (tmp);
	tmp = ft_redir(arbre, ligne, info, lst);
	if (tmp)
		return (tmp);
	tmp = ft_par(arbre, ligne, info, lst);
	if (tmp)
		return (tmp);
	arbre->commande = trim_free(ft_strdup(ligne), " ");
	free(ligne);
	return (arbre);
}

t_arbre	*analyse_syntaxique(char *ligne, t_arbre *arbre, t_info *info)
{
	int		inpar;
	int		lst[2];
	int		insimplegui;
	int		indoublegui;

	insimplegui = 0;
	indoublegui = 0;
	lst[1] = 0;
	inpar = 0;
	arbre = initarbre(arbre, ligne);
	if (arbre)
		return (lanceanal(arbre, ligne, info, lst));
	return (NULL);
}
