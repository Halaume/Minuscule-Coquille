/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:58:20 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/22 20:13:52 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*open_heredoc(char *heredoc)
{
	int		fd;
	char	*ligne;

	fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		printf("cannot open tmp file\n");
	ligne = readline(">");
	while (strcmp(ligne, heredoc))
	{
		write(fd, ligne, ft_strlen(ligne));
		write(fd, "\n", 1);
		free(ligne);
		ligne = readline(">");
	}
	free(ligne);
	free(heredoc);
}

