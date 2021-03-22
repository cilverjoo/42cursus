/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:29 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/22 17:54:21 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int			main(int ac, char **av)
{
	t_ps	*ps;
	
	if (ac > 1)
	{
		ps = init_ps(ac - 1);
		make_stack_list(av, ps);
		read_instruction(ps);
		execute_instrs(ps);
		show_stacks(ps);
		check_is_ok(ps, 1);
		exit(0);
	}
	return (0);
}
