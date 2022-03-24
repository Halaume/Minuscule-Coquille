/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:35:20 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/23 15:13:41 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

size_t	ft_strlcpy(char *dest, char *src, size_t n)
{
	unsigned long	i;

	i = 0;
	if (n != 0)
	{
		while (src[i] && i < n - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
		i = 0;
	}
	while (src[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void	do_my_sec_fork(int argc, char **argv, t_struct *pipex, char **envp)
{
	pipex->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->fd_out < 0)
		error_func(pipex, "open fd_out error\n");
	pipex->forkcmd2 = fork();
	if (pipex->forkcmd2 == -1)
		error_func(pipex, "forkcmd2 error\n");
	if (pipex->forkcmd2 == 0)
		second_fun(pipex, argv, envp);
}
