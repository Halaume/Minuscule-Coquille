/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lance_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 11:43:00 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/05 12:23:43 by tnaton           ###   ########.fr       */
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

char	*getvalfromenvheredoc(char *var, t_info *info, int ingui, char next)
{
	t_env	*current;

	if (!ft_strcmp(var, "$?"))
		return (free(var), ft_itoa(info->exit_status));
	if (!ft_strcmp(var, "$") && (ingui || next == ' ' || next == '\0' || next == '$'))
		return (free(var), ft_strdup("$"));
	else if (!ft_strcmp(var, "$"))
		return (free(var), ft_strdup(""));
	current = info->env;
	while (current && ft_strcmp(var + 1, current->variable))
		current = current->next;
	free(var);
	if (!current)
		return (ft_strdup(""));
	return (ft_strdup(current->valeur));
}

int	futuresizeofexpandedheredoc(char *str, t_info *info)
{
	int		futuresize;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	futuresize = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
		{
			i++;
			futuresize += 1;
		}
		j = i;
		if (str[j] == '$')
			j++;
		while (str[j] && ((str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= 'a' && str[j] <= 'z') || (str[j - 1] == '$' && str[j] == '?')))
			j++;
		if (i != j)
		{
			tmp = getvalfromenvheredoc(ft_substr(str, i, j - i), info, 1, 0);
			futuresize += ft_strlen(tmp);
			free(tmp);
			i = j;
		}
	}
	return (futuresize);
}

char	*expand(char *str, t_info *info)
{
	char	*newstr;
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	k = 0;
	newstr = (char *)malloc(sizeof(char) * (futuresizeofexpandedheredoc(str, info) + 1));
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			newstr[k++] = str[i++];
		j = i;
		if (str[j] == '$')
			j++;
		while (str[j] && ((str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= 'a' && str[j] <= 'z') || (str[j - 1] == '$' && str[j] == '?')))
			j++;
		if (i != j)
		{
			tmp = getvalfromenvheredoc(ft_substr(str, i, j - i), info, 1, 0);
			i = j;
			j = 0;
			while (tmp[j])
				newstr[k++] = tmp[j++];
			free(tmp);
		}
	}
	free(str);
	newstr[k] = '\0';
	return (newstr);
}

int	get_fd_here(char *path, t_info *info)
{
	int		fd;
	int		fd2;
	char	*tmp;
	int		quote;

	quote = asquote(path);
	tmp = ft_strtrim(path, "\"");
	if (!quote)
	{
		fd = open(tmp, O_RDWR);
		path = checkopen(ft_itoa(0));
		fd2 = open(path, O_CREAT | O_RDWR, 00644);
		while (tmp)
		{
			free(tmp);
			tmp = get_next_line(fd);
			if (tmp)
			{
				tmp = expand(tmp, info);
				write (fd2, tmp, ft_strlen(tmp));
			}
		}
		close(fd2);
		fd2 = open(path, O_RDONLY);
		free(tmp);
		free(path);
		return (fd2);
	}
	else
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

t_toyo	*getcommande(t_arbre *arbre, t_info *info)
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
			toyo->in = get_fd_here(arbre->commande, info);
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

t_toyo	*rec_toyo(t_arbre *arbre, t_info *info)
{
	t_toyo	*toyo;

	if (!ft_strcmp(arbre->commande, "|"))
	{
		toyo = getcommande(arbre->fd, info);
		toyo->next = rec_toyo(arbre->fg, info);
		return (toyo);
	}
	toyo = getcommande(arbre, info);
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
		return (toyotage(rec_toyo(arbre, info), info));
	return (exec(getcommande(arbre, info), info));
}
