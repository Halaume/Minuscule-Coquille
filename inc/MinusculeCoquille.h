/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MinusculeCoquille.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:09:23 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/21 13:11:15 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINUSCULECOQUILLE_H
# define MINUSCULECOQUILLE_H

# include "France.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
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

VIDE	analyse_syntaxique(CARACTERE *ligne, t_arbre *arbre);
void	logique(char *ligne, t_info *info, int i);
void	tuyau(char *ligne, t_info *info, int i);
void	fourchette(char *ligne, t_info *info, int i);
char	*no_quote(char *str);
char	**no_quote_tab(char *str);
char	**split_empty_line(char *s, char c);

//				FAIS-DEDANS

int		check_built_in(char *commande);
int		is_built_in(char *arbre, char **envp);
int		ft_echo(char **arg);
int		ft_cd(char **arg, char **envp);
int		ft_pwd(void);
int		ft_export(char **splitted_str);
int		ft_unset(char **splitted_str);
int		ft_env(char **splitted_str);
int		ft_exit(int status);

//				EXECUTION DES COMMANDES

int		exec(char *commande, char **envp);

//				LIBERATION

void	free_char_char(char **str);
void	exit_func(int status);

#endif
