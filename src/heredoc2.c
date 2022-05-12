/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:26:18 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/12 18:39:25 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	asquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*addquote(char *path, char *heredoc)
{
	char	*tmp;
	char	*tmp2;

	if (asquote(heredoc))
	{
		tmp = ft_strjoin("\"", path);
		tmp2 = ft_strjoin(tmp, "\"");
		return (free(path), free(tmp), tmp2);
	}
	return (path);
}

void	ft_lenfant(char *heredoc, char *path)
{
	int		fd;
	char	*tmp;
	char	*ligne;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 0)
		ft_putstr_fd("ne peut pas ouvrir le fichier temporaire\n", 2);
	if (asquote(heredoc))
	{
		tmp = ft_strtrim(heredoc, "<\"");
		heredoc = tmp;
	}
	tmp = ft_strjoin(heredoc, ">");
	ligne = readline(tmp);
	while (ligne && ft_strcmp(ligne, heredoc))
	{
		write(fd, ligne, ft_strlen(ligne));
		write(fd, "\n", 1);
		free(ligne);
		ligne = readline(tmp);
	}
	if (!ligne)
		ft_putstr_fd("fin inattendue mais fin quand meme\n", 2);
	close(fd);
	return (free(ligne), free(tmp), free(heredoc));
}

void	lancefant(char *heredoc, char *path)
{
	signal(SIGINT, SIG_DFL);
	ft_lenfant(heredoc, path);
	exit(0);
}

char	*open_heredoc(char *heredoc, t_info *info)
{
	char	*path;
	pid_t	lenfant;
	int		status;

	status = 0;
	path = checkopen(ft_itoa(0));
	signal(SIGINT, SIG_IGN);
	lenfant = fork();
	if (lenfant < 0)
		return (NULL);
	if (lenfant == 0)
		lancefant(heredoc, path);
	path = addquote(path, heredoc);
	signal(SIGINT, &singal);
	waitpid(lenfant, &status, 0);
	if (status == 2)
	{
		info->exit_status = 130;
		info->caner = 1;
	}
	free(heredoc);
	return (path);
}
