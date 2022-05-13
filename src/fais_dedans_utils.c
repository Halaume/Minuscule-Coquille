/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:22:08 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/13 11:36:00 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/MinusculeCoquille.h"

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
	if ((size_t)i == ft_strlen(env_commande) && \
			ft_strncmp(env_commande, commande, i) == 0)
		return (0);
	return (1);
}

int	check_identifier(char *commande)
{
	int		i;
	char	*commande_check;

	commande_check = NULL;
	if (commande[0] == '=')
		return (0);
	i = (int)ft_strlen(commande);
	while (i > 0 && commande[i - 1] != '=')
		i--;
	if (i == 0)
		return (0);
	commande_check = malloc(sizeof(char) * i + 1);
	ft_strlcpy(commande_check, commande, i);
	i = -1;
	if (ft_isdigit(commande_check[i + 1]))
		return (free(commande_check), 0);
	while (commande_check[++i])
	{
		if (commande_check[i] < '0' || (commande_check[i] > '9' && \
					commande_check[i] < 'A') || commande_check[i] > 'z' || \
				(commande_check[i] > 'Z' && commande_check[i] < '_') || \
				commande_check[i] == '`')
			return (free(commande_check), 0);
	}
	return (free(commande_check), 1);
}

int	norme_export(char *cmd, t_info *info, int i, t_env *tmp)
{
	tmp = info->env;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp && is_this_var(tmp->variable, cmd) == 0)
			{
				while (i > 0)
				{
					if (cmd[i] && (cmd[i - 1] == '=' || cmd[i] == '='))
					{
						free(tmp->valeur);
						if (cmd[i] == '=')
							i++;
						tmp->valeur = ft_substr(cmd, i, ft_strlen(cmd) - i + 1);
						return (0);
					}
					i--;
				}
			}
			tmp = tmp->next;
		}
	}
	return (1);
}

int	ft_export_this(t_info *info, char *cmd)
{
	int		i;

	i = ft_strlen(cmd);
	if (!check_identifier(cmd))
		return (ft_putstr_fd("export: identifier invalide\n", 2), 1);
	if (norme_export(cmd, info, i, NULL) == 0)
		return (0);
	i = ft_strlen(cmd);
	while (i > 0 && cmd[i - 1] != '=')
		i--;
	env_add(&info->env, new_env(ft_substr(cmd, 0, i - 1), \
				ft_substr(cmd, i, ft_strlen(cmd) - i + 1)));
	return (0);
}
