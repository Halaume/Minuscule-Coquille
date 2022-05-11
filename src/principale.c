/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaton <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:44:07 by tnaton            #+#    #+#             */
/*   Updated: 2022/05/11 16:14:27 by tnaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

int	g_exit_status;

void	singal(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	freeprincip(t_info *info, char *ligne, int ac, char **av)
{
	ft_exit(NULL, info);
	free(ligne);
	freeenv(info->env);
	free_char_char(info->envp);
	rl_clear_history();
	(void)ac;
	(void)av;
}

void	lanceprin(char *ligne, t_info *info)
{
	add_history(ligne);
	info->arbre = NULL;
	if (verifieligne(ligne))
	{
		ft_putstr_fd("Erreur syntaxique\n", 2);
		free(ligne);
	}
	else
	{
		info->arbre = analyse_syntaxique(ligne, info->arbre, info);
		if (!checkarbre(info->arbre, info))
			lance_exec(info, info->arbre);
		else
			ft_putstr_fd("Erreur syntaxique\n", 2);
		info->caner = 0;
	}
	if (info->arbre)
	{
		freearbre(info->arbre);
		info->arbre = NULL;
	}
}

int	principale(int ac, char **av, char **envp)
{
	char	*ligne;
	t_info	info;
	char	*tmp;

	g_exit_status = 0;
	initinfo(&info, envp);
	ligne = readline("MinusculeCoquille$>");
	while (ligne)
	{
		if (g_exit_status)
			info.exit_status = g_exit_status;
		tmp = ft_strtrim(ligne, " ");
		if (ft_strlen(tmp))
			lanceprin(ligne, &info);
		else
			free(ligne);
		g_exit_status = 0;
		ligne = readline("MinusculeCoquille$>");
		free(tmp);
	}
	freeprincip(&info, ligne, ac, av);
	return (info.exit_status);
}

int	main(int ac, char **av, char **envp)
{
	return (principale(ac, av, envp));
}
