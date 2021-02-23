/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 23:33:37 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/02/21 17:26:49 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	g_minishell;

void	run_shell(t_shell *minishell)
{
	int tmp_status;

	ft_putstr_fd("=====================================\n", STDOUT);
	ft_putstr_fd(".  .  -  . .  -  .-. . . .-- .   .   \n", STDOUT);
	ft_putstr_fd("|\\/|  |  |\\|  |  '-. |-| |-  |   |   \n", STDOUT);
	ft_putstr_fd("'  '  -  ' '  -  '-' ' ' '-- '-- '-- \n", STDOUT);
	ft_putstr_fd("=====================================\n", STDOUT);
	while (1)
	{
		signal(SIGINT, sighandler_int);
		signal(SIGQUIT, sighandler_quit);
		ft_putstr_fd("MINISHELL$ ", STDOUT);
		if (parsing(minishell) == SUCCESS)
		{
			execute(minishell);
			minishell->wating_child = TRUE;
			while (wait(&tmp_status) > 0)
				;
			minishell->wating_child = FALSE;
		}
		clear_all(minishell, SUCCESS, FALSE);
	}
}

int		init_data(t_shell *minishell)
{
	minishell->cur_dir = getcwd(NULL, 0);
	minishell->pio[READ] = -1;
	minishell->pio[WRITE] = -1;
	minishell->origin_std[READ] = dup(STDIN);
	minishell->origin_std[WRITE] = dup(STDOUT);
	return (SUCCESS);
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	init_data(&g_minishell);
	init_env(&g_minishell, envp);
	make_export_list(&g_minishell);
	run_shell(&g_minishell);
	return (0);
}
