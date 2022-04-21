/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MinusculeCoquille.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:09:23 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/21 17:08:46 by tnaton           ###   ########.fr       */
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

typedef	STRUCTURE s_env
{
	CARACTERE		*variable;
	CARACTERE		*valeur;
	STRUCTURE s_env	*next;
}	t_env;

typedef STRUCTURE s_arbre
{
	CARACTERE			*commande;
	STRUCTURE s_arbre	*fd;
	STRUCTURE s_arbre	*fg;
}	t_arbre;

typedef STRUCTURE s_info
{
	t_env	*env;
	t_arbre	*arbre;
}	t_info;

//				ANALYSE-SYNTAXIQUE

t_arbre	*analyse_syntaxique(CARACTERE *ligne, t_arbre *arbre);
void	logique(char *ligne, t_info *info, int i);
void	tuyau(char *ligne, t_info *info, int i);
void	fourchette(char *ligne, t_info *info, int i);

//				FAIS-DEDANS

int		is_built_in(t_arbre *arbre);
int		ft_echo(t_arbre **arg);
int		ft_cd(t_arbre **arg);
int		ft_pwd(char **splitted_str);
int		ft_export(char **splitted_str);
int		ft_unset(char **splitted_str);
int		ft_env(char **splitted_str);
int		ft_exit(char **splitted_str);

#endif
