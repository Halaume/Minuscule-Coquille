/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lance_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:43:00 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/27 19:31:35 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	get_fd_concat(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 2, ft_strlen(path) - 2);
	fd = open(tmp, O_APPEND | O_WRONLY | O_CREAT, 00644);
	free(tmp);
	return (fd);
}

int	get_fd_out(char *path)
{
	int		fd;
	char	*tmp;

	tmp = ft_substr(path, 1, ft_strlen(path) - 1);
	fd = open(tmp, O_TRUNC | O_WRONLY | O_CREAT, 00644);
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

	tmp = ft_strtrim(path, "\"");
	fd = open(tmp, O_RDONLY);
	free(tmp);
	return (fd);
}

int	isredirect(char *str)
{
	char	*tmp;

	if (!ft_strncmp(str, ">>", 2))
		return (1);
	else if (!ft_strncmp(str, ">", 1))
		return (1);
	else if (!ft_strncmp(str, "<", 1))
		return (1);
	tmp = ft_strtrim(str, "\"");
	if (!ft_strncmp(tmp, "/tmp/.", 6))
		return (free(tmp), 1);
	return (free(tmp), 0);
}

t_toyo	*getcommande(t_arbre *arbre)
{
	t_toyo	*toyo;
	char	*tmp;

	toyo = (t_toyo *)malloc(sizeof(t_toyo));
	toyo->in = 0;
	toyo->out = 1;
	toyo->next = NULL;
	toyo->commande = NULL;
	toyo->arbre = NULL;
	while (arbre && isredirect(arbre->commande))
	{
		if (!ft_strncmp(arbre->commande, ">>", 2))
		{
			if (toyo->out != 1)
				close(toyo->out);
			toyo->out = get_fd_concat(arbre->commande);
		}
		else if (!ft_strncmp(arbre->commande, ">", 1))
		{
			if (toyo->out != 1)
				close(toyo->out);
			toyo->out = get_fd_out(arbre->commande);
		}
		else if (!ft_strncmp(arbre->commande, "<", 1))
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
			tmp = ft_strtrim(arbre->commande, "<");
			perror(tmp);
			free(tmp);
			return (toyo);
		}
		arbre = arbre->fd;
	}
	if (arbre && arbre->commande && !ft_strncmp("()", arbre->commande, 2))
		toyo->arbre = arbre->fd;
	if (arbre)
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
	toyo = getcommande(arbre);
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

int	badet(t_info *info, t_arbre *arbre)
{
	while (!ft_strcmp(arbre->commande, "&&"))
		arbre = arbre->fg;
	if (!ft_strcmp(arbre->commande, "||"))
		return (lance_exec(info, arbre->fg));
	return (0);
}

int	badou(t_info *info, t_arbre *arbre)
{
	while (!ft_strcmp(arbre->commande, "||"))
		arbre = arbre->fg;
	if (!ft_strcmp(arbre->commande, "&&"))
		return (lance_exec(info, arbre->fg));
	return (0);
}

int	lance_exec(t_info *info, t_arbre *arbre)
{
	if (!ft_strcmp(arbre->commande, "&&"))
	{
		if (!lance_exec(info, arbre->fd))
			return (lance_exec(info, arbre->fg));
		else
			return (badet(info, arbre->fg));
	}
	else if (!ft_strcmp(arbre->commande, "||"))
	{
		if (lance_exec(info, arbre->fd))
			return (lance_exec(info, arbre->fg));
		else
			return (badou(info, arbre->fg));
	}
	else if (!ft_strcmp(arbre->commande, "|"))
		return (toyotage(rec_toyo(arbre), info));
	return (exec(getcommande(arbre), info));
}
