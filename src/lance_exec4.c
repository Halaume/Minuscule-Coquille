/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lance_exec4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:54:58 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 15:55:19 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	get_fd_here(char *path, t_info *info)
{
	int		fd;
	int		fd2;
	char	*tmp;
	int		quote;

	quote = asquote(path);
	tmp = ft_strtrim(path, "\"<");
	if (!quote)
	{
		fd = open(tmp, O_RDWR);
		path = checkopen(ft_itoa(0));
		fd2 = open(path, O_CREAT | O_RDWR, 00644);
		ecrit(fd, fd2, info);
		close(fd2);
		fd2 = open(path, O_RDONLY);
		return (free(tmp), free(path), fd2);
	}
	else
		fd = open(tmp, O_RDONLY);
	return (free(tmp), fd);
}

int	isredirect(char *str)
{
	char	*tmp;

	if (!ft_strncmp(str, ">>", 2))
		return (1);
	else if (!ft_strncmp(str, ">", 1))
		return (1);
	else if (!ft_strncmp(str, "<<", 2))
		return (1);
	else if (!ft_strncmp(str, "<", 1))
		return (1);
	tmp = ft_strtrim(str, "\"<");
	if (!ft_strncmp(tmp, "/tmp/.", 6))
		return (free(tmp), 1);
	return (free(tmp), 0);
}

void	leprout(t_arbre *arbre, t_toyo *toyo, t_info *info)
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
		toyo->in = get_fd_here(arbre->commande, info);
	}
}

t_toyo	*init_toyo(t_arbre *arbre)
{
	t_toyo	*toyo;

	toyo = (t_toyo *)malloc(sizeof(t_toyo));
	toyo->in = 0;
	toyo->out = 1;
	toyo->next = NULL;
	toyo->commande = NULL;
	toyo->arbre = arbre;
	return (toyo);
}

t_toyo	*haha(t_toyo *toyo)
{
	toyo->arbre = NULL;
	ft_putstr_fd("Redirection ambigue\n", 2);
	return (toyo);
}
