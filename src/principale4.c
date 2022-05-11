/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principale4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:12:37 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 17:59:28 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

t_env	*ft_getenv(char **envp)
{
	t_getenv	a;

	a.first = NULL;
	a.i = 0;
	while (envp[a.i])
	{
		a.tmp = (t_env *)malloc(sizeof(t_env));
		if (!a.tmp)
			return (NULL);
		a.j = 0;
		while (envp[a.i][a.j])
		{
			if (envp[a.i][a.j] == '=')
			{
				a.tmp->variable = ft_substr(envp[a.i], 0, a.j);
				a.tmp->valeur = ft_substr(envp[a.i], a.j + 1, \
						ft_strlen(envp[a.i]) - a.j);
				movea(&a);
				break ;
			}
			a.j++;
		}
		a.i++;
	}
	return (a.first);
}

void	freeenv(t_env *current)
{
	t_env	*tmp;

	while (current)
	{
		free(current->variable);
		current->variable = NULL;
		free(current->valeur);
		current->valeur = NULL;
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

int	getsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**ft_getenvp(t_env *env)
{
	char	**envp;
	char	*tmp;
	int		i;

	i = 0;
	envp = (char **)malloc(sizeof(char *) * (getsize(env) + 1));
	if (!envp)
		return (NULL);
	while (env && env->variable && env->valeur)
	{
		tmp = ft_strjoin(env->variable, "=");
		if (!tmp)
			return (NULL);
		envp[i++] = ft_strjoin(tmp, env->valeur);
		if (!envp[i - 1])
			return (NULL);
		free(tmp);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	initinfo(t_info *info, char **envp)
{
	info->env = ft_getenv(envp);
	info->envp = ft_getenvp(info->env);
	info->arbre = NULL;
	info->isexport = 0;
	info->caner = 0;
	info->exit_status = 0;
	signal(SIGINT, &singal);
	signal(SIGQUIT, SIG_IGN);
}
