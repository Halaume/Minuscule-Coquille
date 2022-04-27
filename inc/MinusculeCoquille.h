/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MinusculeCoquille.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:09:23 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/27 11:23:44 by ghanquer         ###   ########.fr       */
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
char	**ft_splitsane(char *str);

//				ENVIRONNEMENTALE

char	**ft_getenvp(t_env *env);

//				FAIS-DEDANS

int		check_built_in(char *commande);
int		is_built_in(char *arbre, t_info *info);
int		ft_echo(char **arg);
int		ft_cd(char **arg, char **envp);
int		ft_pwd(void);
int		ft_export(t_env *env, char **commande);
int		ft_unset(t_env *env, char *commande);
int		ft_env(t_env *env);
int		ft_exit(int status);

//				EXECUTION DES COMMANDES

int		exec(t_toyo *toyo, t_info *info);
int		exec(t_toyo *toyo, t_info *info);
int		lance_exec(t_info *info, t_arbre *arbre);
char	*get_my_path(char **envp);
int		check_abs_path(char *argv);
char	*get_cmd(char **path, char *cmd);

//				LIBERATION

void	free_char_char(char **str);
int		exit_func(int status);
void	free_toyo(t_toyo *toyo);

//				PIPEX

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_struct
{
	t_info	*info;
	pid_t	forkcmd1;
	pid_t	forkcmd2;
	pid_t	*pid_tab;
	int		nb_cmd;
	int		indexarg;
	char	*envpath;
	char	**envpathcut;
	char	**arg;
	char	*cmd;
	char	**argv;
	char	**envp;
}	t_struct;

//			STRING MANIP

char		**ft_getenvp(t_env *env);
char		**ft_split(char *s, char c);
char		*ft_join(char *s1, char *s2);
void		ft_putstr(char *str);
void		get_outfile(char *argv, t_struct *pipex);
int			args_min(char *arg, t_struct *pipex);

//			PIPEX FUN

void		first_fun(t_struct *pipex, char **argv, char **envp);
void		spamdup2(int elem1, int elem2);
void		second_fun(t_struct *pipex, char **argv, char **envp);
t_struct	init_pipex(char **argv, char **envp);
void		fun_here_doc(char *argv, t_struct *pipex);
void		child(t_toyo *toyo, t_struct *pipex, int fd[2], int fd1);
int			toyotage(t_toyo *toyo, t_info *info);

//			ERROR / FREE / END PROG

void		error_func(t_struct *pipex, char *msg, char *cmd);
void		free_func(t_struct *pipex);
void		close_pipe(t_struct *pipex);

#endif
