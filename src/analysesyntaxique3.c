/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:36:33 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 15:37:10 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

t_arbre	*reredir(t_arbre *arbre, char *ligne, int *lst, t_info *info)
{
	while (ligne[lst[1]] && ligne[lst[1] + 1] && ligne[lst[1] + 1] == ' ')
		lst[1]++;
	if (ligne[lst[1]] && ligne[lst[1] + 1] == '(')
	{
		arbre->commande = ft_strdup("");
		free(ligne);
		return (arbre);
	}
	arbre->commande = ft_substr(ligne, lst[0], lst[1] - lst[0]);
	arbre->commande = aled(arbre->commande, info);
	arbre->fd = analyse_syntaxique(ft_strjoin_free(ft_substr(ligne, 0, \
				lst[0]), ft_substr(ligne, lst[1], ft_strlen(ligne) - lst[1])), \
			arbre->fd, info);
	free(ligne);
	return (arbre);
}

t_arbre	*redir(t_arbre *arbre, char *ligne, t_info *info, int i)
{
	t_inspi	s;
	int		j;
	int		lst[2];

	s.par = 0;
	j = i + 1;
	if (ligne[i + 1] == ligne[i])
		j++;
	while (ligne[j] && ligne[j] == ' ')
		j++;
	s.simplegui = 0;
	s.doublegui = 0;
	while (ligne[j])
	{
		gui(ligne[j], &s.doublegui, &s.simplegui, &s.par);
		if ((!s.simplegui && !s.doublegui) && (ligne[j] == ' ' || ligne[j] == \
			'>' || ligne[j] == '<' || ligne[j] == '&' || ligne[j] == '|' || \
			ligne[j] == '('))
			break ;
		j++;
	}
	lst[0] = i;
	lst[1] = j;
	return (reredir(arbre, ligne, lst, info));
}

t_arbre	*par(t_arbre *arbre, char *ligne, t_info *info, int *lst)
{
	int	j;

	j = 0;
	while (j != lst[0])
	{
		if (ligne[j] != ' ' && ligne[j] != '(')
		{
			arbre->commande = ft_strdup("");
			free(ligne);
			return (arbre);
		}
		j++;
	}
	arbre->fd = analyse_syntaxique(ft_substr(ligne, lst[0] + 1, lst[1] - \
				lst[0] - 1), arbre->fd, info);
	arbre->commande = ft_strdup("()");
	free(ligne);
	return (arbre);
}

t_arbre	*ft_etou(t_arbre *arbre, char *ligne, t_info *info, int *lst)
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
		if (lst[1] && !insimplegui && !indoublegui && !inpar && ((ligne[lst[1]] \
				== '&' && ligne[lst[1] - 1] == '&') || (ligne[lst[1]] == '|' \
				&& ligne[lst[1] - 1] == '|')))
			return (etou(arbre, ligne, info, lst[1]));
		lst[1]++;
	}
	return (NULL);
}

t_arbre	*ft_pipou(t_arbre *arbre, char *ligne, t_info *info, int *lst)
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
		if (!insimplegui && !indoublegui \
				&& !inpar && (ligne[lst[1]] == '|' && ligne[lst[1] + 1] != '|' \
					&& (!lst[1] || ligne[lst[1] - 1] != '|')))
			return (pipou(arbre, ligne, info, lst[1]));
		lst[1]++;
	}
	return (NULL);
}
