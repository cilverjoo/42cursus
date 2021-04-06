/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:24:13 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/02/21 16:51:03 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void				exit_only(t_token *token)
{
	if (!get_next_pipe(token) && !get_prev_pipe(token))
	{
		clear_all(&g_minishell, 1, 1);
		exit(g_minishell.exit_status);
	}
}

int					is_valid_digit(char *str)
{
	int				i;
	unsigned long	exit_num;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	exit_num = 0;
	while (ft_isdigit(str[i]))
	{
		exit_num = exit_num * 10 + str[i] - '0';
		i++;
	}
	if (i > 19 || exit_num >= 9223372036854775808ULL)
		return (0);
	return (SUCCESS);
}

void				exit_invalid_digit_error(t_shell *minishell, char *cmd)
{
	ft_putstr_fd("minishell: exit: ", STDERROR);
	ft_putstr_fd(cmd, STDERROR);
	ft_putstr_fd(": numeric argument required\n", STDERROR);
	minishell->exit_status = 255;
}

int					cmd_exit(char **cmd, t_shell *minishell, t_token *token)
{
	int				arg_cnt;
	int				i;

	if (!get_next_pipe(token) && !get_prev_pipe(token))
		ft_putstr_fd("exit\n", STDOUT);
	arg_cnt = 0;
	i = 0;
	while (cmd[++arg_cnt])
		if (!is_valid_digit(cmd[arg_cnt]))
		{
			exit_invalid_digit_error(minishell, cmd[arg_cnt]);
			exit_only(token);
			return (ERROR);
		}
	if (arg_cnt > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERROR);
		minishell->exit_status = 1;
		return (ERROR);
	}
	if (arg_cnt == 2)
		minishell->exit_status = ft_atoi(cmd[--arg_cnt]);
	exit_only(token);
	return (SUCCESS);
}
