/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:18:56 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/02/21 16:37:04 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			is_valid_n_option(char *cmd)
{
	int		i;

	if (ft_strcmp(cmd, "-n") == 0)
		return (SUCCESS);
	i = ft_strlen(cmd) - 1;
	if (i == 0)
		return (0);
	while (i > 0 && cmd[0] == '-' && cmd[i] == 'n')
		i--;
	if (i == 0)
		return (SUCCESS);
	return (0);
}

int			cmd_echo(char **cmd)
{
	int		i;
	int		len;
	int		n_flag_check;

	n_flag_check = 0;
	i = 1;
	while (cmd[i] && is_valid_n_option(cmd[i]))
	{
		n_flag_check = 1;
		i++;
	}
	len = 0;
	while (cmd[len])
		len++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT);
		if (i != len - 1)
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (!n_flag_check)
		ft_putstr_fd("\n", STDOUT);
	g_minishell.exit_status = 0;
	return (SUCCESS);
}
