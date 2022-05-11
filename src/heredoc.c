/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:58:20 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 14:31:10 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

char	*newchar(char *str)
{
	int	num;

	num = ft_atoi(str);
	num++;
	free(str);
	return (ft_itoa(num));
}

char	*checkopen(char *str)
{
	int		ret;
	char	*tmp;

	ret = 0;
	while (!ret)
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
	int		i;
	int		j;
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

char	*quoteit(char	*str)
{
	char	*tmp;

	tmp = ft_strjoin("\"", str);
	free(str);
	str = ft_strjoin(tmp, "\"");
	free(tmp);
	return (str);
}

char	*getisexp(char *var, t_info *info, int ingui, char next)
{
	t_env	*current;

	if (!ft_strcmp(var, "$?"))
		return (free(var), quoteit(ft_itoa(info->exit_status)));
	if (!ft_strcmp(var, "$") && (ingui || next == ' ' || next == '\0' \
			|| next == '$'))
		return (free(var), ft_strdup("$"));
	else if (!ft_strcmp(var, "$"))
		return (free(var), ft_strdup(""));
	current = info->env;
	while (current && ft_strcmp(var + 1, current->variable))
		current = current->next;
	free(var);
	if (!current)
		return (ft_strdup(""));
	return (quoteit(ft_strdup(current->valeur)));
}

char	*getisnotexp(char *var, t_info *info, int ingui, char next)
{
	t_env	*current;

	if (!ft_strcmp(var, "$?"))
		return (free(var), ft_itoa(info->exit_status));
	if (!ft_strcmp(var, "$") && (ingui || next == ' ' || next == '\0' \
				|| next == '$'))
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

char	*getvalfromenv(char *var, t_info *info, int ingui, char next)
{
	if (info->isexport)
		return (getisexp(var, info, ingui, next));
	else
		return (getisnotexp(var, info, ingui, next));
}

int	getfuturesizeoftheexpandedshit(char *del, int i, t_info *info, int ingui)
{
	int		j;
	char	*var;

	j = i;
	while (del[j] && ((del[j] >= 'A' && del[j] <= 'Z') \
				|| (del[j] >= 'a' && del[j] <= 'z') || (del[j] == '$' \
					|| del[j] == '?')))
	{
		if (j != i && del[j] == '$')
			break ;
		j++;
	}
	var = ft_substr(del, i, j - i);
	var = getvalfromenv(var, info, ingui, del[j]);
	j = ft_strlen(var);
	return (free(var), j);
}

int	isdelgood(char *str, int i)
{
	return (str[i] && (((str[i] >= 'A' && str[i] <= 'Z') \
					|| (str[i] >= 'a' && str[i] <= 'z') || (str[i] == '$')) \
			|| (i && str[i] == '?' && str[i - 1] == '$')));
}

void	pf(char *ret, char *del, int *j, int *i)
{
	while (*j < *i)
	{
		ret[*j] = del[*j];
		(*j)++;
	}
}

char	*changedel(char *del, int *i, t_info *info, int ingui)
{
	char	*ret;
	int		lenexpanded;
	int		j;
	int		souvenir;

	souvenir = *i;
	j = 0;
	lenexpanded = getfuturesizeoftheexpandedshit(del, *i, info, ingui);
	ret = (char *)malloc(sizeof(char *) * (ft_strlen(del) + lenexpanded));
	pf(ret, del, &j, i);
	while (isdelgood(del, *i))
	{
		if ((souvenir != *i && del[*i] == '$') || (*i && del[*i - 1] == '?'))
			break ;
		*i += 1;
	}
	ret[j] = '\0';
	ret = ft_strjoin_free(ret, getvalfromenv(ft_substr(del, j, *i - j), info, \
				ingui, del[*i]));
	ret = ft_strjoin_free(ret, ft_substr(del, *i, ft_strlen(del) - *i));
	*i = souvenir + lenexpanded - 1;
	return (free(del), ret);
}

void	initshit(int *i, int *j, int *insimplegui, int *indoublegui)
{
	*i = 0;
	*j = 1;
	*insimplegui = 0;
	*indoublegui = 0;
}

char	*get_del(char *del, t_info *info, int *asex, int caca)
{
	t_del	d;
	char	*tmp;

	tmp = ft_strtrim(del, " ");
	free(del);
	del = tmp;
	d.list = (int *)malloc(sizeof(int) * (ft_strlen(del) + 1));
	initshit(&d.i, &d.j, &d.sg, &d.dg);
	while (del[d.i])
	{
		gui(del[d.i], &d.dg, &d.sg, NULL);
		if ((!d.sg && del[d.i] == '"') || (!d.dg && del[d.i] == '\''))
			d.list[d.j++] = d.i;
		if (caca && (!d.sg && del[d.i] == '$'))
		{
			*asex = 1;
			del = changedel(del, &d.i, info, (d.sg || d.dg));
			if (!ft_strlen(del))
				break ;
		}
		d.i++;
	}
	d.list[0] = d.j - 1;
	return (rmquote(del, d.list));
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
