/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:19:15 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/11 15:09:28 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

void	write_it(char **arg, int is_n_here, t_toyo *toyo, int i)
{
	int	first_word;

	first_word = 1;
	if (arg[i])
	{
		while (arg[i])
		{
			if (first_word == 0)
				write(toyo->out, " ", 1);
			write(toyo->out, arg[i], ft_strlen(arg[i]));
			if (first_word == 1)
				first_word = 0;
			i++;
		}
	}
	if (is_n_here == 0)
		write (toyo->out, "\n", 1);
}

int	ft_echo(char **arg, t_toyo *toyo)
{
	int	i;
	int	is_n_here;

	i = 1;
	is_n_here = 0;
	if (arg[1] && !ft_strcmp(arg[1], "") && !arg[2])
		return (write(toyo->out, "\n", 1), 0);
	if (arg[1] && ft_strcmp(arg[1], "-n") == 0)
	{
		while (arg[i] && ft_strncmp(arg[i], "-n", ft_strlen(arg[i])) == 0)
			i++;
		is_n_here = 1;
	}
	write_it(arg, is_n_here, toyo, i);
	if (toyo->out != 1)
		close(toyo->out);
	return (0);
}

char	*get_my_home(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp && ft_strncmp("HOME", tmp->variable, 4) != 0)
	{
		tmp = tmp->next;
		if (tmp == NULL)
			return (NULL);
	}
	if (!tmp)
		return (NULL);
	return (tmp->valeur);
}

int	lencaca(char **prout)
{
	int	wiwi;

	wiwi = 0;
	if (prout)
	{
		while (prout[wiwi])
		wiwi++;
	}
	return (wiwi);
}

void	init_sdsm(t_sdsm *s, char *str)
{
	s->j = 0;
	s->i = 0;
	s->insimplegui = 0;
	s->indoublegui = 0;
	s->nbword = countword(str);
	s->par = 0;
}
