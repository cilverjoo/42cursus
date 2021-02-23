/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:22:39 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/02/21 16:36:20 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		cmd_pwd(t_shell *minishell)
{
	ft_putstr_fd(minishell->cur_dir, STDOUT);
	ft_putstr_fd("\n", STDOUT);
	minishell->exit_status = 0;
	return (SUCCESS);
}
