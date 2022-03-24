/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 18:00:25 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/23 15:11:35 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	pid_t	forkcmd1;
	pid_t	forkcmd2;
	int		ma_pipe[2];
	int		fd_in;
	int		fd_out;
	int		exec_return;
	char	*envpath;
	char	**envpathcut;
	char	**arg;
	char	*cmd;
}	t_struct;

//			STRING MANIP

int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char *s, char c);
size_t		ft_strlcpy(char *dest, char *src, size_t n);
char		*ft_join(char *s1, char *s2);
void		ft_putstr(char *str);

//			PIPEX FUN

void		first_fun(t_struct *pipex, char **argv, char **envp);
void		second_fun(t_struct *pipex, char **argv, char **envp);
char		*get_cmd(char **path, char *cmd);
t_struct	init_pipex(void);
char		*get_my_path(char **envp);
int			check_abs_path(char **argv, int j);
void		do_my_sec_fork(int argc, char **argv, t_struct *pipex, char **envp);

//			ERROR

void		error_func(t_struct *pipex, char *msg);
void		free_func(t_struct *pipex);

#endif
