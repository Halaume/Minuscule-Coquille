/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:58:20 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/23 18:51:20 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*newchar(char *str)
{
	int	num;

	num = ft_atoi(str);
	num++;
	free(str);
	return(ft_itoa(num));
}

char	*checkopen(char *str)
{
	int		ret;
	char	*tmp;

	ret = 0;
	while(!ret)
	{
		tmp = ft_strjoin("/tmp/.", str);
		ret = access(tmp, F_OK);
		if (!ret)
		{
			free(tmp);
			str = newchar(str);
		}
	}
	free(str);
	return (tmp);
}

int	isinlist(int num, int *list)
{
	int	i;

	i = 1;
	while (i < list[0] + 1)
	{
		if (list[i] == num)
			return (1);
		i++;
	}
	return (0);
}

char	*rmquote(char *del, int *list)
{
	int	i;
	int	j;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(del) - list[0] + 1));
	i = 0;
	j = 0;
	while (del[i])
	{
		if (!isinlist(i, list))
			tmp[j++] = del[i++];
		else
			i++;
	}
	tmp[j] = '\0';
	free(del);
	free(list);
	return (tmp);
}

char	*get_del(char *del)
{
	int	i;
	int	insimplegui;
	int	indoublegui;
	int *list;
	int	j;

	list = (int *)malloc(sizeof(int) * (ft_strlen(del) + 1));
	i = 0;
	j = 1;
	insimplegui = 0;
	indoublegui = 0;
	while (del[i])
	{
		if (!indoublegui && del[i] == '\'')
			insimplegui = !insimplegui;
		if (!insimplegui && del[i] == '"')
			indoublegui = !indoublegui;
		if ((!insimplegui && del[i] == '"') || (!indoublegui && del[i] == '\''))
		{
			list[j] = i;
			j++;
		}
		i++;
	}
	list[0] = j - 1;
	return (rmquote(del, list));
}

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

char	*open_heredoc(char *heredoc)
{
	int		fd;
	char	*ligne;
	char	*path;
	char	*tmp;

	path = checkopen(ft_itoa(0));
	path = addquote(path, heredoc);
	heredoc = get_del(heredoc);
	ligne = ft_strtrim(path, "\"");
	fd = open(ligne, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		printf("cannot open tmp file\n");
	free(ligne);
	tmp = ft_strjoin(heredoc, ">");
	ligne = readline(tmp);
	while (strcmp(ligne, heredoc))
	{
		write(fd, ligne, ft_strlen(ligne));
		write(fd, "\n", 1);
		free(ligne);
		ligne = readline(tmp);
	}
	close(fd);
	return (free(ligne), free(tmp), free(heredoc), path);
}
