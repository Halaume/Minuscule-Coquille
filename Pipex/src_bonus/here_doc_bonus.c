/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:34:31 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/23 10:48:18 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	write_pipe(int nb)
{
	int	tmp;

	tmp = nb - 1;
	while (tmp > 0)
	{
		write(1, "pipe ", 5);
		tmp--;
	}
	write(1, "heredoc> ", 9);
}

int	test_limiter(char *buf, char *str)
{
	if (ft_strlen(buf) - 1 != ft_strlen(str))
		return (0);
	else if (ft_strncmp(buf, str, ft_strlen(buf) - 1) == 0)
		return (1);
	return (0);
}

void	fun_here_doc(char *argv, t_struct *pipex)
{
	int		still_in;
	int		file;
	char	*buf;

	still_in = 1;
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file < 0)
		error_func(pipex, "Open error");
	while (still_in == 1)
	{
		write_pipe(pipex->nb_cmd);
		buf = get_next_line(0);
		if (buf == NULL)
			error_func(pipex, "\nBuffer is NULL\n");
		if (test_limiter(buf, argv) == 1)
			still_in = 0;
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	close(file);
	pipex->fd_in = open(".heredoc_tmp", O_RDONLY);
	if (pipex->fd_in < 0)
		ft_putstr("Heredoc error\n");
}
