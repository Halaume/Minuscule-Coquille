/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysesyntaxique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:30:44 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/28 12:33:49 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

void	prendpart(char *ligne, t_arbre *arbre, int *start)
{
	int	end;
	int	inpar;
	int	ingui;

	inpar = 0;
	ingui = 0;
	(void)arbre;
	end = *start;
	if (ligne[end] == '(')
		inpar++;
	if (ligne[end + 1])
		end++;
	while (ligne[end] && ((ligne[end] != '|' && ligne[end] != '&' && ligne[end] != '<' && ligne[end] != '>') || (inpar || ingui)))
	{
		if (!ingui && ligne[end] == '(')
			inpar++;
		if (!ingui && ligne[end] == ')')
			inpar--;
		if (ligne[end] == '\'' || ligne[end] == '"')
			ingui = !ingui;
		end++;
	}
	if (ligne[end])
		end++;
	printf("prendpart : %s\n", ft_substr(ligne, *start, (end - *start)));
	*start = end - 2;
}

void	getpar(char *ligne, t_arbre *arbre, int *start)
{
	int	end;
	int	inpar;
	int	ingui;

	ingui = 0;
	inpar = 1;
	(void)arbre;
	end = *start + 1;
	while (inpar != 0)
	{
		if (ligne[end] == '\'')
			ingui = !ingui;
		if (ligne[end] == '"')
			ingui = !ingui;
		if (!ingui && ligne[end] == '(')
			inpar++;
		if (!ingui && ligne[end] == ')')
			inpar--;
		end++;
	}
	printf("getpar : %s\n", ft_substr(ligne, *start, (end - *start)));
	*start = end - 2;
}

void	takelogical(char *ligne, t_arbre *arbre, int i)
{
	int	j;
	int	inpar;
	int	indoublegui;
	int	insimplegui;

	insimplegui = 0;
	indoublegui = 0;
	inpar = 0;
	j = i - 2;
	(void)arbre;
	while (j)
	{
		if (!indoublegui && ligne[j] == '\'')
		   insimplegui = !insimplegui;
		if (!insimplegui && ligne[j] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[j] == ')')
			inpar++;
		if (!insimplegui && !indoublegui && ligne[j] == '(')
			inpar--;
		if (j && !indoublegui && !insimplegui && inpar <= 0 && ((ligne[j] == '|' && ligne[j - 1] == '|') || (ligne[j] == '&' && ligne[j - 1] == '&')))
			break ;
		j--;
	}
	printf("%s\n", ft_substr(ligne, j, i - j));
}

void	takepipe(char *ligne, t_arbre *arbre, int i)
{
	int	j;
	int	inpar;
	int	indoublegui;
	int	insimplegui;

	insimplegui = 0;
	indoublegui = 0;
	inpar = 0;
	j = i - 2;
	(void)arbre;
	while (j)
	{
		if (!indoublegui && ligne[j] == '\'')
		   insimplegui = !insimplegui;
		if (!insimplegui && ligne[j] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[j] == ')')
			inpar++;
		if (!insimplegui && !indoublegui && ligne[j] == '(')
			inpar--;
		if (j && !indoublegui && !insimplegui && !inpar && (ligne[j] == '|' || ligne[j] == '&'))
			break ;
		j--;
	}
	printf("%s\n", ft_substr(ligne, j, i - j));
}

void	takerepipe(char *ligne, t_arbre *arbre, int i)
{
	int	j;
	int	inpar;
	int	indoublegui;
	int	insimplegui;

	insimplegui = 0;
	indoublegui = 0;
	inpar = 0;
	j = i + 1;
	(void)arbre;
	while (ligne[j])
	{
		if (!indoublegui && ligne[j] == '\'')
		   insimplegui = !insimplegui;
		if (!insimplegui && ligne[j] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[j] == ')')
			inpar--;
		if (!insimplegui && !indoublegui && ligne[j] == '(')
			inpar++;
		if (j && !indoublegui && !insimplegui && !inpar && (ligne[j] == '|' || ligne[j] == '&'))
			break ;
		j++;
	}
	printf("%s\n", ft_substr(ligne, i, j - i));
}

void	takefork(char *ligne, t_arbre *arbre, int i)
{
	int	j;
	int	inpar;
	int	indoublegui;
	int	insimplegui;

	insimplegui = 0;
	indoublegui = 0;
	inpar = 0;
	j = i;
	while (j)
	{
		if (!indoublegui && ligne[j] == '\'')
		   insimplegui = !insimplegui;
		if (!insimplegui && ligne[j] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[j] == ')')
			inpar++;
		if (!insimplegui && !indoublegui && ligne[j] == '(')
			inpar--;
		if (j && !inpar && !indoublegui && !insimplegui && !inpar && ligne[j] == '(')
			break ;
		j--;
	}
	if (i)
		analyse_syntaxique(ft_substr(ligne, j + 1, i - j - 1), arbre);
}

void	analyse_syntaxique(char *ligne, t_arbre *arbre)
{
	int	i;
	int	inpar;
	int	insimplegui;
	int	indoublegui;
	int	logical;
	int	fork;

	fork = 0;
	logical = 0;
	insimplegui = 0;
	indoublegui = 0;
	inpar = 0;
	i = 0;
	if (!ligne)
		RENVOIE ;
	while (ligne[i])
	{
		if (!indoublegui && ligne[i] == '\'')
		   insimplegui = !insimplegui;
		if (!insimplegui && ligne[i] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[i] == ')')
			inpar--;
		if (!insimplegui && !indoublegui && ligne[i] == '(')
			inpar++;
		if (i && !insimplegui && !indoublegui && !inpar && ((ligne[i] == '&' && ligne[i - 1] == '&') \
			|| (ligne[i] == '|' && ligne[i - 1] == '|')))
		{
			logical++;
			takelogical(ligne, arbre, i);
		}
		i++;
	}
	if (logical)
		takelogical(ligne, arbre, i);
	i = 0;
	inpar = 0;
	insimplegui = 0;
	indoublegui = 0;
	while (ligne[i])
	{
		if (!indoublegui && ligne[i] == '\'')
		   insimplegui = !insimplegui;
		if (!insimplegui && ligne[i] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[i] == ')')
			inpar--;
		if (!insimplegui && !indoublegui && ligne[i] == '(')
			inpar++;
		if (i && i < (int)ft_strlen(ligne) && !insimplegui && !indoublegui \
				&& !inpar && (ligne[i] == '|' && ligne[i + 1] != '|' \
					&& ligne[i - 1] != '|'))
		{
			takepipe(ligne, arbre, i);
			takerepipe(ligne, arbre, i);
		}
		i++;
	}
	inpar = 0;
	insimplegui = 0;
	indoublegui = 0;
	i = 0;
	while (ligne[i])
	{
		if (!indoublegui && ligne[i] == '\'')
		   insimplegui = !insimplegui;
		if (!insimplegui && ligne[i] == '"')
			indoublegui = !indoublegui;
		if (!insimplegui && !indoublegui && ligne[i] == '(')
			inpar++;
		if (!insimplegui && !indoublegui && ligne[i] == ')')
			inpar--;
		if (!inpar && !insimplegui && !indoublegui && ligne[i] == ')')
		{
			fork++;
			takefork(ligne, arbre, i);
		}
		i++;
	}
}
