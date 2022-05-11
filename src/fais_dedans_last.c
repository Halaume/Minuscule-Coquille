/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fais_dedans_last.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:23:39 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/11 12:24:03 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/MinusculeCoquille.h"

int	ft_export(t_info *info, char **commande)
{
	int	i;

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
	commande_check = ft_strdup(commande);
	i = 0;
	if (ft_isdigit(commande_check[i]))
		return (free(commande_check), 0);
	while (commande_check[i])
	{
		if (commande_check[i] < '0' || (commande_check[i] > '9' && \
					commande_check[i] < 'A') || commande_check[i] >= 'z' || \
				(commande_check[i] > 'Z' && commande_check[i] < '_') || \
				commande_check[i] == '`')
			return (free(commande_check), 0);
		i++;
	}
	return (free(commande_check), 1);
}

int	is_this_var_unset(char *env_commande, char *commande)
{
	int	i;

	i = ft_strlen(commande);
	if (i == 0)
		return (1);
	if ((size_t)i == ft_strlen(env_commande) && \
			ft_strncmp(env_commande, commande, i) == 0)
		return (0);
	return (1);
}

void	norme_unset_this(t_env *tmp, t_info *info, t_env *keep)
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
}

int	ft_unset_this(t_info *info, char *commande)
{
	t_env	*tmp;
	t_env	*keep;

	tmp = info->env;
	if (!check_identifier_unset(commande))
		return (ft_putstr_fd("unset: identifier invalide\n", 2), 1);
	while (tmp)
	{
		if (is_this_var_unset(tmp->variable, commande) == 0)
			return (norme_unset_this(tmp, info, keep), 0);
		keep = tmp;
		tmp = tmp->next;
	}
	return (0);
}
