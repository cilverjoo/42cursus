/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:11:00 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/18 01:10:10 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_ps		*init_ps(void)
{
	t_ps	*ps;
	
	ps = (t_ps *)malloc(sizeof(t_ps));
	ps->len = 0;
	ps->is_sorted = 0;
	ps->stack_a = ft_lstnew(NULL);
	ps->stack_b = ft_lstnew(NULL);
	ps->instr = ft_lstnew(NULL);
	return (ps);
}

int			exit_program(void)
{
	char	*error;

	error = "Error\n";
	write(2, error, 6);
	exit(0);
}