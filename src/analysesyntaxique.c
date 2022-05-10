/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/10 15:27:57 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*vireconcat(char *str, t_info *info)
{
	char	*tmp;
	int		asex;

	tmp = ft_strtrim(str, " >");
	free(str);
	str = get_del(tmp, info, &asex, 1);
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
	str = get_del(tmp, info, &asex, 1);
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
	str = get_del(tmp, info, &asex, 0);
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
	str = get_del(tmp, info, &asex, 1);
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
		str = get_del(tmp, info, &asex, 0);
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

t_arbre	*pipou(t_arbre *arbre, char *ligne, t_info *info, int i)
{
	int	j;

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
	int	j;
	int	insimplegui;
	int	indoublegui;
	int	lst[2];

	j = i + 1;
	if (ligne[i + 1] == ligne[i])
		j++;
	while (ligne[j] && ligne[j] == ' ')
		j++;
	insimplegui = 0;
	indoublegui = 0;
	while (ligne[j])
	{
		gui(ligne[j], &indoublegui, &insimplegui, NULL);
		if ((!insimplegui && !indoublegui) && (ligne[j] == ' ' || ligne[j] == \
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
	arbre->commande = ft_strdup(ligne);
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
