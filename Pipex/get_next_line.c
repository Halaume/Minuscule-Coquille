/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:51:00 by ghanquer          #+#    #+#             */
/*   Updated: 2022/03/06 16:49:03 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

char	*ft_join_gnl(char *line, char *buffer)
{
	char	*str;
	int		j;

	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffer) + 1));
	if (!str)
		return (NULL);
	j = fill_line(line, str, j, -1);
	if (line)
		free(line);
	j = fill_line(buffer, str, j, -1);
	str[j] = '\0';
	return (str);
}

char	*get_line(int fd, char *line)
{
	char	*buffer;
	int		res;

	res = 1;
	buffer = NULL;
	while (res == 1)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		res = read(fd, buffer, BUFFER_SIZE);
		if (res <= 0 && !line)
		{
			free(buffer);
			return (NULL);
		}
		buffer[res] = '\0';
		line = ft_join_gnl(line, buffer);
		free(buffer);
		if (res)
			res = check_line(line);
	}
	return (line);
}

char	*del_start(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (line)
		while (line[i] && line[i] != '\n')
			i++;
	else
		return (NULL);
	tmp = malloc(sizeof(char) * ((ft_strlen(line) - i) + 2));
	if (!tmp)
		return (NULL);
	if (line)
		if (line[i] == '\n')
			i++;
	j = fill_line(line, tmp, j, i - 1);
	tmp[j] = '\0';
	if (tmp[0] == '\0')
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

char	*get_start(char *line)
{
	int		i;
	int		j;
	char	*start;

	j = 0;
	i = 0;
	if (line)
	{
		while (line[i] && line[i] != '\n')
			i++;
		start = malloc(i + 2);
		if (!start)
			return (NULL);
		while (i >= 0)
		{
			start[j] = line[j];
			j++;
			i--;
		}
		free(line);
		start[j] = '\0';
		return (start);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*str;

	if (fd < 0 || fd > 1024)
		return (NULL);
	if (!line)
		line = NULL;
	str = NULL;
	str = get_line(fd, line);
	if (!str)
	{
		free(str);
		return (NULL);
	}
	line = del_start(str);
	str = get_start(str);
	if (!line)
		free(line);
	if (!str)
		return (NULL);
	return (str);
}
