/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:00:25 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/16 14:20:56 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include "get_next_line.h"

typedef struct s_struct
{
	pid_t	forkcmd1;
	pid_t	forkcmd2;
	pid_t	*pid_tab;
	int		fd_in;
	int		fd_out;
	int		is_heredoc;
	int		nb_cmd;
	int		nb_pipe;
	int		indexarg;
	char	*envpath;
	char	**envpathcut;
	char	**arg;
	char	*cmd;
	char	**argv;
	char	**envp;
}	t_struct;

//			PARSING

void		get_infile(char **argv, t_struct *pipex, int argc);
void		get_outfile(char *argv, t_struct *pipex);

//			STRING MANIP

int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char *s, char c);
size_t		ft_strlcpy(char *dest, char *src, size_t n);
char		*ft_join(char *s1, char *s2);
void		ft_putstr(char *str);
void		get_outfile(char *argv, t_struct *pipex);
int			args_min(char *arg, t_struct *pipex);

//			PIPEX FUN

t_struct	check_start(int argc, char **argv, char **envp);
void		first_fun(t_struct *pipex, char **argv, char **envp);
void		spamdup2(int elem1, int elem2);
void		second_fun(t_struct *pipex, char **argv, char **envp);
char		*get_cmd(char **path, char *cmd);
t_struct	init_pipex(char **argv, char **envp);
char		*get_my_path(char **envp);
int			check_abs_path(char **argv, int j);
void		fun_here_doc(char *argv, t_struct *pipex);
void		child(t_struct *pipex, int fd[2], int fd1);

//			ERROR / FREE / END PROG

void		error_func(t_struct *pipex, char *msg);
void		free_func(t_struct *pipex);
void		close_pipe(t_struct *pipex);

#endif
