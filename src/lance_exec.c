/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lance_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:43:00 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/24 19:25:28 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MinusculeCoquille.h"

int	get>>fd(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 2, ft_strlen(path) - 2);
	fd = open(tmp, O_APPEND | O_WRONLY | O_CREAT);
	free(tmp);
	return (fd);
}

int	get>fd(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 1, ft_strlen(path) - 1);
	fd = open(tmp, O_TRUNC | O_WRONLY | O_CREAT);
	free(tmp);
	return (fd);
}

int	get<fd(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 1, ft_strlen(path) - 1);
	fd = open(tmp, O_RDONLY);
	free(tmp);
	return (fd);
}

int	get<<fd(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 6, ft_strlen(path) - 6);
	fd = open(tmp, O_RDONLY);
	free(tmp);
	return (fd);
}

t_toyo	*getcommande(t_arbre *arbre)
{
	t_toyo	*toyo;

	toyo = (t_toyo *)malloc(sizeof(toyo));
	toyo->in = 0;
	toyo->out = 1;
	while (arbre->fd)
	{
		if (ft_strncmp(arbre->commande, ">>"), 2)
		{
			if (toyo->out != 1)
				close(toyo->out);
			toyo->in = get>>fd(arbre->commande);
		}
		else if (ft_strncmp(arbre->commande, ">"), 1)
		{
			if (toyo->out != 1)
				close(toyo->out);
			toyo->out = get>fd(arbre->commande);
		}
		else if (ft_strncmp(arbre->commande, "<"), 1)
		{
			if (toyo->in != 0)
				close(toyo->in);
			toyo->in = get<fd(arbre->commande);
		}
		else
		{
			if (toyo->in != 0)
				close(toyo->in);
			toyo->in = get<<fd(arbre->commande);
		}
		arbre = arbre->fd;
	}
	toyo->commande = arbre->commande;
	return (toyo);
}

t_toyo	*rec_toyo(t_arbre *arbre)
{
	t_toyo	*toyo;

	if (!ft_strcmp(arbre->commande, "|"))
	{
		toyo = getcommande(arbre->fd);
		toyo->next = rec_toyo(arbre->fg, in, out);
		return (toyo);
	}
	toyo = (t_toyo *)malloc(sizeof(t_toyo));
	toyo->in = 0;
	toyo->out = 1;
	toyo->commande = arbre->commande;
	toyo->next = NULL;
	return (toyo);
}

int	lance_toyo(t_info *info, t_toyo *toyo)
{
	char	**pipe;
	t_toyo	*current;
	int	i;

	i = 0;
	current = toyo;
	while (current)
	{
		current = current->next;
		i++;
	}
	pipe = (char **)malloc(sizeof(char *) * i + 1);
	pipe[i] = NULL;
	i = 0;
	current = toyo;
	while (current)
	{
		pipe[i++] = current->commande;
		current = current->next;
	}
	return (pipex(pipe));
}

int	lance_exec(t_info *info, t_arbre *arbre, int in, int out)
{
	if (!ft_strcmp(arbre->commande, "&&"))
	{
		if (lance_exec(info, arbre->fd, 0, 1))
			return (lance_exec(info, arbre->fg, 0, 1));
	}
	else if (!ft_strcmp(arbre->commande, "||"))
	{
		if (!lance_exec(info, arbre->fd, 0, 1))
			return (lance_exec(info, arbre->fg, 0, 1));
	}
	else if (!ft_strcmp(arbre->commande, "|"))
		return (lance_toyo(info, rec_toyo(arbre)));
	else
		return (exec(arbre->commande));
}