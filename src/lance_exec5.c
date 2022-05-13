/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lance_exec5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:55:28 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/13 12:47:12 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

t_toyo	*getcommande(t_arbre *arbre, t_info *info)
{
	t_toyo	*toyo;
	char	*tmp;

	toyo = init_toyo(arbre);
	while (arbre && isredirect(arbre->commande))
	{
		arbre->commande = vireguillemet(arbre->commande, info);
		if (!arbre->commande)
			return (haha(toyo));
		leprout(arbre, toyo, info);
		if (toyo->in < 0 || toyo->out < 0)
		{
			tmp = ft_strtrim(arbre->commande, "<");
			perror(tmp);
			toyo->arbre = NULL;
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

void	freetoyo(t_toyo *toyo)
{
	t_toyo	*current;

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
