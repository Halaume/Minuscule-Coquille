/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MinusculeCoquille.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:09:23 by tnaton            #+#    #+#             */
/*   Updated: 2022/03/24 15:23:19 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINUSCULECOQUILLE_H
# define MINUSCULECOQUILLE_H

# include "France.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef STRUCTURE s_arbre
{
	CARACTERE			*commande;
	STRUCTURE s_arbre	**logique;
	STRUCTURE s_arbre	**tuyau;
	STRUCTURE s_arbre	*fourchette;
	STRUCTURE s_arbre	**argument;
}	t_arbre;

typedef STRUCTURE s_info
{
	t_arbre	*arbre;
}	t_info;

//				ANALYSE-SYNTAXIQUE

VIDE	analyse_syntaxique(CARACTERE *ligne, t_info *info);

//				FAIS-DEDANS

int		is_built_in(char *str);
int		ft_echo(char **splitted_str);
int		ft_cd(char **splitted_str);
int		ft_pwd(char **splitted_str);
int		ft_export(char **splitted_str);
int		ft_unset(char **splitted_str);
int		ft_env(char **splitted_str);
int		ft_exit(char **splitted_str);

#endif
