/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/09 17:35:46 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*vireconcat(char *str, t_info *info)
{
	char	*tmp;
	int		asex;

	tmp = ft_strtrim(str, " >");
	free(str);
	str = get_del(tmp, info, &asex);
	if (!ft_strlen(str) && asex)
		return (free(str), NULL);
	tmp = ft_strjoin(">>", str);
	free(str);
	return (tmp);
}

char	*vireout(char *str, t_info *info)
{
	char	*tmp;
	int		asex;

	tmp = ft_strtrim(str, " >");
	free(str);
	str = get_del(tmp, info, &asex);
	if (!ft_strlen(str) && asex)
		return (free(str), NULL);
	tmp = ft_strjoin(">", str);
	free(str);
	return (tmp);
}

char	*virehere(char *str, t_info *info)
{
	char	*tmp;
	int		quote;
	int		asex;

	tmp = ft_strtrim(str, " <");
	quote = asquote(tmp);
	free(str);
	str = get_del(tmp, info, &asex);
	if (!ft_strlen(str) && asex)
		return (free(str), NULL);
	tmp = ft_strjoin("<<", str);
	if (quote)
	{
		free(str);
		str = ft_strjoin("\"", tmp);
		free(tmp);
		tmp = ft_strjoin(str, "\"");
	}
	free(str);
	return (tmp);
}

char	*virein(char *str, t_info *info)
{
	char	*tmp;
	int		asex;

	tmp = ft_strtrim(str, " <");
	free(str);
	str = get_del(tmp, info, &asex);
	if (!ft_strlen(str) && asex)
		return (free(str), NULL);
	tmp = ft_strjoin("<", str);
	free(str);
	return (tmp);
}

char	*vireguillemet(char *str, t_info *info)
{
	if (!ft_strncmp(str, ">>", 2))
		return (vireconcat(str, info));
	else if (!ft_strncmp(str, ">", 1))
		return (vireout(str, info));
	else if (!ft_strncmp(str, "<<", 2))
		return (virehere(str, info));
	else if (!ft_strncmp(str, "<", 1))
		return (virein(str, info));
	return (str);
}

char	*aled(char *str, t_info *info)
{
	char	*tmp;
	int		quote;
	int		asex;

	if (!ft_strncmp(str, "<<", 2))
	{
		tmp = ft_strtrim(str, " <");
		quote = asquote(tmp);
		free(str);
		str = get_del(tmp, info, &asex);
		if (!ft_strlen(str) && asex)
			return (free(str), NULL);
		tmp = ft_strjoin("<<", str);
		if (quote)
		{
			free(str);
			str = ft_strjoin("\"", tmp);
			free(tmp);
			tmp = ft_strjoin(str, "\"");
		}
		free(str);
		return (tmp);
	}
	return (str);
}

void	gui(char c, int *dg, int *sg, int *p)
{
	if (!*dg && c == '\'')
		*sg = !*sg;
	else if (!*sg && c == '"')
		*dg = !*dg;
	else if (!*sg && !*dg && c == ')')
		(*p)--;
	else if (!*sg && !*dg && c == '(')
		(*p)++;
}

t_arbre	*etou(t_arbre *arbre, char *ligne, t_info *info, int i)
{
	int	j;

	arbre->fd = analyse_syntaxique(ft_substr(ligne, 0, i - 1), arbre->fd, info);
	j = i;
	while (ligne[j])
		j++;
	arbre->fg = analyse_syntaxique(ft_substr(ligne, i + 1, j), arbre->fg, info);
	if (ligne[i] == '|')
		arbre->commande = ft_strdup("||");
	if (ligne[i] == '&')
		arbre->commande = ft_strdup("&&");
	free(ligne);
	return (arbre);
}

t_arbre	*analyse_syntaxique(char *ligne, t_arbre *arbre, t_info *info)
{
	int		i;
	int		inpar;
	int		insimplegui;
	int		indoublegui;
	int		first_par;
	int		j;
	char	*tmp;

	insimplegui = 0;
	indoublegui = 0;
	inpar = 0;
	i = 0;
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
	while (ligne[i])
	{
		gui(ligne[i], &indoublegui, &insimplegui, &inpar);
		if (i && !insimplegui && !indoublegui && !inpar && ((ligne[i] == '&'\
			&& ligne[i - 1] == '&') || (ligne[i] == '|' \
				&& ligne[i - 1] == '|')))
		{
		}
		i++;
	}
	i = 0;
	inpar = 0;
	insimplegui = 0;
	indoublegui = 0;
	while (ligne[i])
	{
		gui(ligne[i], &indoublegui, &insimplegui, &inpar);
		if (!insimplegui && !indoublegui \
				&& !inpar && (ligne[i] == '|' && ligne[i + 1] != '|' \
					&& (!i || ligne[i - 1] != '|')))
		{
			arbre->fd = analyse_syntaxique(ft_substr(ligne, 0, i), arbre->fd, \
					info);
			j = i;
			while (ligne[j])
				j++;
			arbre->fg = analyse_syntaxique(ft_substr(ligne, i + 1, j), \
					arbre->fg, info);
			arbre->commande = ft_strdup("|");
			free(ligne);
			return (arbre);
		}
		i++;
	}
	i = 0;
	inpar = 0;
	insimplegui = 0;
	indoublegui = 0;
	while (ligne[i])
	{
		gui(ligne[i], &indoublegui, &insimplegui, &inpar);
		if (!insimplegui && !indoublegui && !inpar && (ligne[i] == '<' || \
					ligne[i] == '>'))
		{
			j = i + 1;
			if (ligne[i + 1] == ligne[i])
				j++;
			while (ligne[j] && ligne[j] == ' ')
				j++;
			insimplegui = 0;
			indoublegui = 0;
			while (ligne[j])
			{
				if (!indoublegui && ligne[j] == '\'')
					insimplegui = !insimplegui;
				if (!insimplegui && ligne[j] == '"')
					indoublegui = !indoublegui;
				if ((!insimplegui && !indoublegui) && (ligne[j] == ' ' \
							|| ligne[j] == '>' || ligne[j] == '<' \
							|| ligne[j] == '&' || ligne[j] == '|' \
							|| ligne[j] == '('))
					break ;
				j++;
			}
			while (ligne[j] && ligne[j + 1] && ligne[j + 1] == ' ')
				j++;
			if (ligne[j] && ligne[j + 1] == '(')
			{
				arbre->commande = ft_strdup("");
				free(ligne);
				return (arbre);
			}
			arbre->commande = ft_substr(ligne, i, j - i);
			arbre->commande = aled(arbre->commande, info);
			arbre->fd = analyse_syntaxique(ft_strjoin_free(ft_substr(ligne, 0, \
							i), ft_substr(ligne, j, ft_strlen(ligne) - j)), \
					arbre->fd, info);
			free(ligne);
			return (arbre);
		}
		i++;
	}
	inpar = 0;
	insimplegui = 0;
	indoublegui = 0;
	i = 0;
	first_par = 0;
	while (ligne[i])
	{
		gui(ligne[i], &indoublegui, &insimplegui, &inpar);
		if (!inpar && !first_par && !insimplegui && !indoublegui \
				&& ligne[i] == '(')
			first_par = i;
		if (!inpar && !insimplegui && !indoublegui && ligne[i] == ')')
		{
			j = 0;
			while (j != first_par)
			{
				if (ligne[j] != ' ' && ligne[j] != '(')
				{
					arbre->commande = ft_strdup("");
					free(ligne);
					return (arbre);
				}
				j++;
			}
			arbre->fd = analyse_syntaxique(ft_substr(ligne, first_par + 1, i - \
						first_par - 1), arbre->fd, info);
			arbre->commande = ft_strdup("()");
			free(ligne);
			return (arbre);
		}
		i++;
	}
	arbre->commande = ft_strdup(ligne);
	free(ligne);
	return (arbre);
}
