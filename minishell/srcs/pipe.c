/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:21:23 by heryu             #+#    #+#             */
/*   Updated: 2021/02/18 14:21:55 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prev_pipe_redir(int *pio)
{
	if (pio[READ] != -1)
	{
		dup2(pio[READ], STDIN);
		close(pio[READ]);
	}
}

void	next_pipe_redir(int *pio)
{
	pipe(pio);
	dup2(pio[WRITE], STDOUT);
	close(pio[WRITE]);
}
