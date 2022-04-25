/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MinusculeCoquille.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:09:23 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/25 16:32:21 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINUSCULECOQUILLE_H
# define MINUSCULECOQUILLE_H

# include "France.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef	STRUCTURE s_toyo
{
	CARACTERE			*commande;	
	ENTIER				in;
	ENTIER				out;
	STRUCTURE s_toyo	*next;
}	t_toyo;

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
	char	**envp;
	t_env	*env;
	t_arbre	*arbre;
	int		exit_status;
}	t_info;

//				ANALYSE-SYNTAXIQUE

t_arbre	*analyse_syntaxique(CARACTERE *ligne, t_arbre *arbre);
void	logique(char *ligne, t_info *info, int i);
void	tuyau(char *ligne, t_info *info, int i);
void	fourchette(char *ligne, t_info *info, int i);
char	*no_quote(char *str);
char	**no_quote_tab(char *str);
char	**split_empty_line(char *s, char c);
char	*strjoin_space(char *s1, char *s2);
char	*open_heredoc(char *heredoc);
char	*get_del(char *del);

//				STRING MANIP

char	*no_quote(char *str);
char	**no_quote_tab(char *str);
char	**split_empty_line(char *s, char c);
char	*strjoin_space(char *s1, char *s2);

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

int		exec(t_toyo *toyo, t_info *info);
int		lance_exec(t_info *info, t_arbre *arbre);

//				LIBERATION

void	free_char_char(char **str);
int		exit_func(int status);
void	free_toyo(t_toyo *toyo);

#endif
