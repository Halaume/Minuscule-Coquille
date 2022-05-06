/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:07:38 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/06 17:27:11 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	ft_echo(char **arg)
{
	int	i;
	int	is_n_here;
	int	first_word;

	first_word = 1;
	i = 1;
	is_n_here = 0;
	if (arg[1] && !ft_strcmp(arg[1], "") && !arg[2])
		return (write(1, "\n", 1), 0);
	if (arg[1] && ft_strcmp(arg[1], "-n") == 0)
	{
		while (arg[i] && ft_strncmp(arg[i], "-n", ft_strlen(arg[i])) == 0)
			i++;
		is_n_here = 1;
	}
	if (arg[i])
	{
		while (arg[i])
		{
			if (first_word == 0)
				write(1, " ", 1);
			write(1, arg[i], ft_strlen(arg[i]));
			if (first_word == 1)
				first_word = 0;
			i++;
		}
	}
	if (is_n_here == 0)
		write (1, "\n", 1);
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
	int wiwi;

	wiwi = 0;
	while (prout[wiwi])
		wiwi++;
	return (wiwi);
}

int	ft_cd(char **arg, t_info *info)
{
	char	*home;

	if (lencaca(arg) > 2)
		return (write(2, "cd: arguments trop nombreux\n", 24), 1);
	if (lencaca(arg) < 2)
	{
		home = get_my_home(info->env);
		if (home == NULL)
			return (write(2, "coquille: cd: HOME non set\n", 27), 1);
		else		
			if (chdir(home) == -1)
				return (perror("cd"), 1);
	}
	if (chdir(arg[1]) == -1)
		return (perror("cd"), 1);
	return (0);
}

int	ft_pwd(void)
{
	char	curdir[4096];

	if (getcwd(curdir, sizeof(curdir)) == NULL)
		return (perror("erreur pwd wtf"), -1000);
	else
	{
		write(1, curdir, ft_strlen(curdir));
		write(1, "\n", 1);
	}
	return (0);
}

int	is_exiting(char *numero)
{
	int	i;

	i = 0;
	if (numero[i] == '-' || numero[i] == '+')
		i++;
	while (numero[i])
	{
		if (!ft_isdigit(numero[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **exit, t_info *info)
{
	int	i;

	i = 0;
	if (exit)
	{
		if (exit[1])
		{
			while (exit[1][i])
			{
				if (is_exiting(exit[1]))
				{
					ft_putstr_fd("exit: Besoin argument numerique\n", 2);
					info->exit_status = 2;
					break ;
				}
				else
					info->exit_status = ft_atoi(exit[1]);
				i++;
			}
		}
	}
	ft_putstr_fd("exit\n", 1);
	exit_func(info);
	return (0);
}

int	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd(tmp->variable, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(tmp->valeur, 1);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	return (0);
}

int	is_this_var(char *env_commande, char *commande)
{
	int	i;

	i = ft_strlen(commande);
	while (i > 0 && commande[i] != '=')
		i--;
	if (i == 0)
		return (1);
	if (ft_strncmp(env_commande, commande, i) == 0)
		return (0);
	return (1);
}

int	check_identifier(char *commande)
{
	int		i;
	char	*commande_check;

	commande_check = NULL;
	i = (int)ft_strlen(commande);
	while (i > 0 && commande[i - 1] != '=')
		i--;
	if (i == 0)
		return (0);
	commande_check = malloc(sizeof(char) * i + 1);
	ft_strlcpy(commande_check, commande, i);
	i = 0;
	if (ft_isdigit(commande_check[i]))
		return (free(commande_check), 0);
	while (commande_check[i])
	{
	if (commande_check[i] < '0' || (commande_check[i] > '9'  && commande_check[i] < 'A') || commande_check[i] >= 'z' || (commande_check[i] > 'Z' && commande_check[i] < '_') || commande_check[i] == '`')
			return (free(commande_check), 0);
		i++;
	}
	return (free(commande_check), 1);
}

int	ft_export_this(t_info *info, char *commande)
{
	int		i;
	t_env	*tmp;

	i = ft_strlen(commande);
	if (!check_identifier(commande))
		return (ft_putstr_fd("export: identifier invalide\n", 2), 1);
	tmp = info->env;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp && is_this_var(tmp->variable, commande) == 0)
			{
				while (i > 0)
				{
					if (commande[i] && commande[i - 1] == '=')
					{
						free(tmp->valeur);
						tmp->valeur = ft_substr(commande, i, ft_strlen(commande) - i + 1);
						return (0);
					}
					i--;
				}
			}
			tmp = tmp->next;
		}
	}
	i = ft_strlen(commande);
	while (i > 0 && commande[i - 1] != '=')
		i--;
	env_add(&info->env, new_env(ft_substr(commande, 0, i - 1), ft_substr(commande, i, ft_strlen(commande) - i + 1)));
	return (0);
}

int	ft_export(t_info *info, char **commande)
{
	int		i;

	i = 1;
	if (commande[i])
	{
		while (commande[i])
		{
			info->exit_status = ft_export_this(info, commande[i]);
			i++;
		}
	}
	return (info->exit_status);
}

int	check_identifier_unset(char *commande)
{
	int		i;
	char	*commande_check;

	commande_check = NULL;
	i = (int)ft_strlen(commande);
	while (i > 0 && commande[i - 1] != '=')
		i--;
	commande_check = malloc(sizeof(char) * i + 1);
	ft_strlcpy(commande_check, commande, i);
	i = 0;
	if (ft_isdigit(commande_check[i]))
		return (free(commande_check), 0);
	while (commande_check[i])
	{
	if (commande_check[i] < '0' || (commande_check[i] > '9'  && commande_check[i] < 'A') || commande_check[i] >= 'z' || (commande_check[i] > 'Z' && commande_check[i] < '_') || commande_check[i] == '`')
			return (free(commande_check), 0);
		i++;
	}
	return (free(commande_check), 1);
}


int	ft_unset(t_info *info, char *commande)
{
	t_env	*tmp;
	t_env	*keep;

	tmp = info->env;
	if (!check_identifier_unset(commande))
		return (ft_putstr_fd("unset: identifier invalide\n", 2), 1);
	while (tmp)
	{
		if (is_this_var(tmp->variable, commande) == 0)
		{
			if (tmp == info->env)
			{
				info->env = info->env->next;
				free(tmp->variable);
				free(tmp->valeur);
				tmp->variable = NULL;
				tmp->valeur = NULL;
				free(tmp);
			}
			else
			{
				keep->next = tmp->next;
				free(tmp->variable);
				free(tmp->valeur);
				tmp->variable = NULL;
				tmp->valeur = NULL;
				free(tmp);
			}
			return (0);
		}
		keep = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int	is_built_in(char *commande, t_info *info)
{
	char	**no_quote_commande;
	int		ret;

	if (!commande || !*commande)
		return (1);
	ret = 1;
	no_quote_commande = NULL;
	no_quote_commande = ft_splitsane(commande, info);
	if (!no_quote_commande)
		return (1);
	if (ft_strlen(no_quote_commande[0]) == ft_strlen("echo") && ft_strncmp("echo", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_echo(no_quote_commande);
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("pwd") && ft_strncmp("pwd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_pwd();
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("cd") && ft_strncmp("cd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_cd(no_quote_commande, info);
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("export") && ft_strncmp("export", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_export(info, no_quote_commande);
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("unset") && ft_strncmp("unset", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_unset(info, no_quote_commande[1]);
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("env") && ft_strncmp("env", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_env(info->env);
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("exit") && ft_strncmp("exit", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		ret = ft_exit(no_quote_commande, info);
	free_char_char(info->envp);
	info->envp = ft_getenvp(info->env);
	free_char_char(no_quote_commande);
	return (ret);
}

int	check_built_in(char *commande, t_info *info)
{
	char	**no_quote_commande;

	if (!commande || !*commande)
		return (1);
	no_quote_commande = NULL;
	no_quote_commande = ft_splitsane(commande, info);
	if (!no_quote_commande)
		return (1);
	if (ft_strlen(no_quote_commande[0]) == ft_strlen("echo") && ft_strncmp("echo", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("pwd") && ft_strncmp("pwd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("cd") && ft_strncmp("cd", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("export") && ft_strncmp("export", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("unset") && ft_strncmp("unset", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("env") && ft_strncmp("env", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	else if (ft_strlen(no_quote_commande[0]) == ft_strlen("exit") && ft_strncmp("exit", no_quote_commande[0], ft_strlen(no_quote_commande[0])) == 0)
		return (free_char_char(no_quote_commande), 0);
	return (free_char_char(no_quote_commande), 1);
}
