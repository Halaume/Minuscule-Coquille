/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:58:20 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/07 13:55:01 by tnaton           ###   ########.fr       */
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

char	*getvalfromenv(char *var, t_info *info, int ingui, char next)
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

int	getfuturesizeoftheexpandedshit(char *del, int i, t_info *info, int ingui)
{
	int		j;
	char	*var;

	j = i;
	while (del[j] && ((del[j] >= 'A' && del[j] <= 'Z') || (del[j] >= 'a' && del[j] <= 'z') || (del[j] == '$' || del[j] == '?')))
	{
		if (j != i && del[j] == '$')
			break;
		j++;
	}
	var = ft_substr(del, i, j - i);
	var = getvalfromenv(var, info, ingui, del[j]);
	j = ft_strlen(var);
	return (free(var), j);
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
	while (j < *i)
	{
		ret[j] = del[j];
		j++;
	}
	while (del[*i] && ((del[*i] >= 'A' && del[*i] <= 'Z') || (del[*i] >= 'a' && del[*i] <= 'z') || (del[*i] == '$' || del[*i] == '?')))
	{
		if (souvenir != *i && del[*i] == '$')
			break;
		*i += 1;
	}
	ret[j] = '\0';
	ret = ft_strjoin_free(ret, getvalfromenv(ft_substr(del, j, *i - j), info, ingui, del[*i]));
	ret = ft_strjoin_free(ret, ft_substr(del, *i, ft_strlen(del) - *i));
	*i = souvenir + lenexpanded - 1;
	return (free(del), ret);
}

char	*get_del(char *del, t_info *info, int *asex)
{
	int	i;
	int	insimplegui;
	int	indoublegui;
	int		*list;
	int		j;
	char	*tmp;

	tmp = ft_strtrim(del, " ");
	free(del);
	del = tmp;
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
		if ((!insimplegui && del[i] == '$'))
		{
			*asex = 1;
			del = changedel(del, &i, info, (insimplegui || indoublegui));
			if (!ft_strlen(del))
				break;
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
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd < 0)
		printf("cannot open tmp file\n");
	path = addquote(path, heredoc);
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
		write(1, "\n", 1);
	close(fd);
	return (free(ligne), free(tmp), free(heredoc), path);
}
