/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MinusculeCoquille.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:09:23 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/14 10:22:48 by ghanquer         ###   ########.fr       */
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
# include <dirent.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/uio.h>
# include <string.h>
# include <errno.h>
# include "../src/gnl/get_next_line.h"

typedef struct s_sheesh
{
	int		i;
	int		tmp;
	char	*tmpfile;
	char	*file;
}	t_sheesh;

typedef struct s_inshallah
{
	int	j;
	int	i;
}	t_inshallah;

typedef struct s_inspi
{
	int	simplegui;
	int	doublegui;
	int	par;
}	t_inspi;

typedef struct s_splitsane
{
	char	**dest;
	int		nbword;
	int		i;
	int		j;
	int		insimplegui;
	int		indoublegui;
	int		last;
	int		asexpanded;
}	t_splitsane;

typedef struct s_sdsm
{
	int	nbword;
	int	i;
	int	j;
	int	insimplegui;
	int	indoublegui;
	int	last;
	int	par;
}	t_sdsm;

typedef struct s_exp
{
	int	i;
	int	j;
	int	k;
}	t_exp;

typedef struct s_del
{
	int	i;
	int	j;
	int	sg;
	int	dg;
	int	*list;
}	t_del;

typedef STRUCTURE s_toyo
{
	CARACTERE			*commande;	
	STRUCTURE s_arbre	*arbre;
	ENTIER				in;
	ENTIER				out;
	STRUCTURE s_toyo	*next;
}	t_toyo;

typedef STRUCTURE s_env
{
	CARACTERE		*variable;
	CARACTERE		*valeur;
	STRUCTURE s_env	*next;
}	t_env;

typedef struct s_getenv
{
	t_env	*first;
	t_env	*tmp;
	t_env	*current;
	int		i;
	int		j;
}	t_getenv;

typedef STRUCTURE s_name
{
	CARACTERE			*name;
	int					type;
	STRUCTURE s_name	*next;
}	t_name;

typedef STRUCTURE s_arbre
{
	CARACTERE			*commande;
	STRUCTURE s_arbre	*fd;
	STRUCTURE s_arbre	*fg;
}	t_arbre;

typedef STRUCTURE s_info
{
	int		**list;
	int		caner;
	int		isexport;
	char	**envp;
	t_env	*env;
	t_arbre	*arbre;
	int		exit_status;
}	t_info;

typedef STRUCTURE s_ouvrir
{
	DIR				*my_dir;
	struct dirent	*rd;
}	t_ouvrir;

//				ANALYSE-SYNTAXIQUE

t_arbre		*analyse_syntaxique(CARACTERE *ligne, t_arbre *arbre, t_info *info);
void		logique(char *ligne, t_info *info, int i);
void		tuyau(char *ligne, t_info *info, int i);
void		fourchette(char *ligne, t_info *info, int i);
char		*no_quote(char *str);
char		**no_quote_tab(char *str);
char		**split_empty_line(char *s, char c);
char		*strjoin_space(char *s1, char *s2);
char		*open_heredoc(char *heredoc, t_info *info);
char		*get_del(char *del, t_info *info, int *asex, int caca);
char		*checkopen(char *str);
void		singal(int sig);
void		gui(char c, int *db, int *sb, int *p);
void		cmdsig(int sig);

//				STRING MANIP
int			asquote(char *str);
char		*no_quote(char *str);
char		**no_quote_tab(char *str);
char		**split_empty_line(char *s, char c);
char		*strjoin_space(char *s1, char *s2);
char		**ft_splitsane(char *str, t_info *info);
void		init_sdsm(t_sdsm *s, char *str);
int			countword(char *str);
char		**ft_splitdesesmorts(char	*str);
int			countall(char **list);
void		initsplit(t_del *d, char **list, int size);
int			asspace(char *str);
char		**splitagedesesmorts(char **list, int size);
char		*vireguillemet(char *str, t_info *info);

//				ENVIRONNEMENTALE

char		**ft_getenvp(t_env *env);
t_env		*new_env(char *str, char *valeur);
t_env		*env_last(t_env *lst);
void		env_add(t_env **alst, t_env *new);

//				FAIS-DEDANS

int			check_built_in(t_toyo *commande, t_info *info);
int			is_built_in(t_toyo *arbre, t_info *info);
int			ft_echo(char **arg, t_toyo *toyo);
int			ft_cd(char **arg, t_info *info);
int			ft_pwd(t_toyo *toyo);
int			ft_export(t_info *info, char **commande);
int			ft_unset(t_info *info, char **commande);
int			ft_env(t_env *env, t_toyo *toyo);
int			ft_exit(char **status, t_info *info);
char		*get_my_home(t_env *env);
int			ft_export_this(t_info *info, char *cmd);
int			ft_unset_this(t_info *info, char *commande);

//				EXECUTION DES COMMANDES

int			exec(t_toyo *toyo, t_info *info);
int			exec(t_toyo *toyo, t_info *info);
int			lance_exec(t_info *info, t_arbre *arbre);
char		*get_my_path(char **envp);
int			check_abs_path(char *argv);
char		*get_cmd(char **path, char *cmd);
int			executing(t_toyo *toyo, t_info *info);
void		norme_executing(t_toyo *toyo, t_info *info, char **arg);

//				LIBERATION

void		free_char_char(char **str);
void		exit_func(t_info *info);
void		free_toyo(t_toyo *toyo);
void		freeenv(t_env *env);
void		freearbre(t_arbre *arbre);
void		free_name(t_name *list);

//				WildCards

void		lst_add(t_name **alst, t_name *list);
t_name		*new_lst(char *str, int type);
char		**cartes_sauvages(char *arg, int *list);
char		**add_wildcard(char **cmd, t_info *info);
char		*jc(char *oui, char *non);
int			lbs(char *str);
int			check_wildcard(char *str);
int			is_good_word(char *arg, t_name *fic, int *list);
int			nb_of_good_word(char *arg, t_name *name, int *list);
int			norme_good(char *arg, t_name *fic, int *list, int i);
int			norme_good2(int i, int j, t_name *fic, char *arg);
int			lbs(char *str);
char		**norme_carte(char *arg, char **ret, t_name *fichier, int *list);
int			count_prof(char *str);
int			osef(int *lst, int i);

//				PIPEX

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
	int		fd1;
}	t_struct;

//			STRING MANIP

char		**ft_getenvp(t_env *env);
char		**ft_split(char *s, char c);
char		*ft_join(char *s1, char *s2);
void		ft_putstr(char *str);
void		get_outfile(char *argv, t_struct *pipex);
int			args_min(char *arg, t_struct *pipex);
int			lencaca(char **prout);

//			PIPEX FUN

void		first_fun(t_struct *pipex, char **argv, char **envp);
void		spamdup2(int elem1, int elem2);
void		second_fun(t_struct *pipex, char **argv, char **envp);
t_struct	init_pipex(char **argv, char **envp);
void		fun_here_doc(char *argv, t_struct *pipex);
void		child(t_toyo *toyo, t_struct *pipex, int fd[2], t_info *i);
int			toyotage(t_toyo *toyo, t_info *info);

//			ERROR / FREE / END PROG

void		error_func(t_struct *pipex, char *msg, char *cmd);
void		free_func(t_struct *pipex);
void		close_pipe(t_struct *pipex);

//			NORME / CHIANT / RELOU

int			getfuturesizeoftheexpandedshit(char *del, int i, \
		t_info *info, int ingui);
char		*getvalfromenv(char	*prout, t_info *info, int ig, char l);
char		*rmquote(char *del, int *chiant);
t_arbre		*redir(t_arbre *a, char *c, t_info *i, int l);
t_arbre		*par(t_arbre *a, char *c, t_info *i, int *l);
t_arbre		*ft_etou(t_arbre *a, char *c, t_info *i, int *l);
t_arbre		*ft_pipou(t_arbre *a, char *c, t_info *i, int *l);
char		*aled(char *c, t_info *i);
t_arbre		*etou(t_arbre *a, char *c, t_info *i, int l);
t_arbre		*pipou(t_arbre *a, char *c, t_info *i, int l);
char		*vireconcat(char *c, t_info *i);
char		*vireout(char *c, t_info *i);
char		*virehere(char *c, t_info *i);
char		*virein(char *c, t_info *i);
int			badet(t_info *i, t_arbre *a);
int			badou(t_info *i, t_arbre *a);
t_toyo		*rec_toyo(t_arbre *a, t_info *i);
t_toyo		*getcommande(t_arbre *a, t_info *i);
char		*getvalfromenvhd(char *c, t_info *i, int k, char j);
int			isadel(char *s, int i);
void		ecrit(int f, int fd, t_info *i);
int			get_fd_concat(char *c);
int			get_fd_out(char *c);
int			get_fd_in(char *c);
t_toyo		*init_toyo(t_arbre *a);
int			isredirect(char *c);
t_toyo		*haha(t_toyo *toyo);
void		leprout(t_arbre *a, t_toyo *t, t_info *i);
int			verifieligne(char *ligne);
void		freearbrecmd(t_arbre *arbre);
void		freearbre(t_arbre *arbre);
int			ischiant(t_arbre *arbre);
int			istropchiant(char *tmp);
int			ft_ischiant(t_arbre *arbre, t_info *info);
int			ft_istropchiant(t_arbre *a, t_info *info);
int			casseburne(t_arbre *arbre);
int			checkarbre(t_arbre *arbre, t_info *info);
void		movea(t_getenv	*a);
t_env		*ft_getenv(char **envp);
void		freeenv(t_env *current);
int			getsize(t_env *env);
char		**ft_getenvp(t_env *env);
void		singal(int signal);
void		initinfo(t_info *info, char **envp);
void		freeprincip(t_info *info, char *ligne, int ac, char **av);
void		indexeage(char *str, t_info *info);
char		*expand(char *str, t_info *info);
int			fsizeofexheredoc(char *str, t_info *info);
void		crever(t_exp *e, t_info *info, char *str);
void		freelist(int **list);
int			potage(char *str, t_name *file, int *list);
char		*re_expand(char *str, t_info *info);
int			aaaaa(char *str, int *isex, t_info *info);
void		lamourir(char *str, t_info *info, int *isex, t_exp *s);
int			*lamort(char *str, t_info *info);
void		initcrie(t_inspi *s, int *i, int *j);
void		hurle(int *isex, int i, t_inspi *s, char *str);
int			*crie(char *str, int *isex, t_info *info);
int			*getlist(int i, int *lst, int last, int countgui);
void		kk(t_inspi *s, int *last, int *k, int *i);
void		cc(t_inspi *s, char *str, int i);
void		prout(char *str, t_exp *e, int *insimplegui);
int			refsizeofexheredoc(char *str, t_info *info);
void		re_smalex(char *str, int *j, int *i);
void		tocard(char *str, t_exp *e, int *insimplegui, char *newstr);
void		initcaner(t_exp *e, int *gui);

#endif
