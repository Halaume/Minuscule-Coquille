/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lance_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:43:00 by tnaton            #+#    #+#             */
/*   Updated: 2022/04/25 16:24:24 by ghanquer         ###   ########.fr       */
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

t_toyo	*getcommande(t_arbre *arbre)
{
	t_toyo	*toyo;

	toyo = (t_toyo *)malloc(sizeof(t_toyo));
	toyo->in = 0;
	toyo->out = 1;
	toyo->next = NULL;
	while (arbre->fd)
	{
		printf("%s\n", arbre->commande);
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

int	lance_exec(t_info *info, t_arbre *arbre)
{
	if (!ft_strcmp(arbre->commande, "&&"))
	{
		if (!lance_exec(info, arbre->fd))
			return (lance_exec(info, arbre->fg));
	}
	else if (!ft_strcmp(arbre->commande, "||"))
	{
		if (lance_exec(info, arbre->fd))
			return (lance_exec(info, arbre->fg));
		else
			return (info->exit_status);
	}
	else if (!ft_strcmp(arbre->commande, "|"))
		return (lance_toyo(info, rec_toyo(arbre)));
	return (exec(getcommande(arbre), info));
}
