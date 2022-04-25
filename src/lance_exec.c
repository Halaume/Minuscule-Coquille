/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lance_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:43:00 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/25 13:07:11 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MinusculeCoquille.h"

int	get_fd_concat(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 2, ft_strlen(path) - 2);
	fd = open(tmp, O_APPEND | O_WRONLY | O_CREAT);
	free(tmp);
	return (fd);
}

int	get_fd_out(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 1, ft_strlen(path) - 1);
	fd = open(tmp, O_TRUNC | O_WRONLY | O_CREAT);
	free(tmp);
	return (fd);
}

int	get_fd_in(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 1, ft_strlen(path) - 1);
	fd = open(tmp, O_RDONLY);
	free(tmp);
	return (fd);
}

int	get_fd_here(char *path)
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
		if (ft_strncmp(arbre->commande, ">>", 2))
		{
			if (toyo->out != 1)
				close(toyo->out);
			toyo->in = get_fd_concat(arbre->commande);
		}
		else if (ft_strncmp(arbre->commande, ">", 1))
		{
			if (toyo->out != 1)
				close(toyo->out);
			toyo->out = get_fd_out(arbre->commande);
		}
		else if (ft_strncmp(arbre->commande, "<", 1))
		{
			if (toyo->in != 0)
				close(toyo->in);
			toyo->in = get_fd_in(arbre->commande);
		}
		else
		{
			if (toyo->in != 0)
				close(toyo->in);
			toyo->in = get_fd_here(arbre->commande);
		}
		if (toyo->in < 0 || toyo->out < 0)
		{
			toyo->commande = NULL;
			return (toyo);
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
		toyo->next = rec_toyo(arbre->fg);
		return (toyo);
	}
	toyo = getcommande(arbre->fg);
	toyo->next = NULL;
	return (toyo);
}

void freetoyo(t_toyo *toyo)
{
	t_toyo *current;

	current = toyo;
	while (current)
	{
		toyo = current;
		current = current->next;
		free(toyo);
	}
	free(current);
}

int	lance_toyo(t_info *info, t_toyo *toyo)
{
	return (pipex(info, toyo));
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
		return (exec(getcommande(arbre), info));
}
