/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:19:57 by ghanquer          #+#    #+#             */
/*   Updated: 2022/05/13 12:46:58 by ghanquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MinusculeCoquille.h"

void	cmdsig(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("Quitte (noyau vidé)\n", 1);
	if (sig == SIGINT)
		write(1, "\n", 1);
}

void	do_my_fork(t_toyo *toyo, t_info *info, int *status)
{
	pid_t	forking;

	forking = fork();
	if (forking == 0)
	{
		lance_exec(info, toyo->arbre);
		exit(info->exit_status);
	}
	waitpid(forking, status, 0);
	free_toyo(toyo);
}

int	fork_for_me(t_toyo *toyo, t_info *info, int *status)
{
	pid_t	my_pid;

	my_pid = fork();
	if (my_pid < 0)
		return (write(2, "fork error\n", 12), -1);
	signal(SIGINT, &cmdsig);
	signal(SIGQUIT, &cmdsig);
	if (my_pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		dup2(toyo->in, 0);
		dup2(toyo->out, 1);
		executing(toyo, info);
	}
	waitpid(my_pid, status, 0);
	signal(SIGINT, &singal);
	signal(SIGQUIT, SIG_IGN);
	free_toyo(toyo);
	return (0);
}

int	norme_exec(t_toyo *toyo, t_info *info, int *status)
{
	*status = check_built_in(toyo, info);
	if (*status == 0)
	{
		info->exit_status = is_built_in(toyo, info);
		free_toyo(toyo);
		return (info->exit_status);
	}
	if (fork_for_me(toyo, info, status) == -1)
		return (-1);
	if (*status == 2 || *status == 131)
	{
		if (*status == 2)
			info->exit_status = 130;
		else
			info->exit_status = 131;
		freearbre(info->arbre);
		info->arbre = NULL;
	}
	return (0);
}

int	exec(t_toyo *toyo, t_info *info)
{
	int		status;

	if (!toyo->arbre)
		return (free_toyo(toyo), 1);
	if (!toyo->commande)
		return (free_toyo(toyo), 0);
	if (!ft_strncmp("()", toyo->commande, 2))
		return (do_my_fork(toyo, info, &status), status);
	if (toyo == NULL)
		return (info->exit_status);
	if (norme_exec(toyo, info, &status) == -1)
		return (-1);
	if (WIFEXITED(status))
	{
		info->exit_status = WEXITSTATUS(status);
		return (info->exit_status);
	}
	return (0);
}
