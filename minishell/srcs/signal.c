/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:08:30 by heryu             #+#    #+#             */
/*   Updated: 2021/02/24 17:24:54 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sighandler_int(int signum)
{
	(void)signum;
	if (g_minishell.pid == 0 && g_minishell.wating_child == FALSE)
	{
		clear_line(&g_minishell, SIGINT);
		ft_putstr_fd("\b\b  \n", STDERROR);
		ft_putstr_fd("MINISHELL$ ", STDOUT);
		g_minishell.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERROR);
		g_minishell.exit_status = 130;
		g_minishell.exit_child = TRUE;
	}
}

void	sighandler_quit(int signum)
{
	(void)signum;
	if (g_minishell.pid == 0 && g_minishell.wating_child == FALSE)
	{
		ft_putstr_fd(g_minishell.line, STDERROR);
		ft_putstr_fd("\b\b  \b\b", STDERROR);
	}
	else
	{
		ft_putstr_fd("Quit: 3\n", STDERROR);
		g_minishell.exit_status = 131;
		g_minishell.exit_child = TRUE;
	}
}