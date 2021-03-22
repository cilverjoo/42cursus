/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:29 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/21 15:32:49 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

int			main(int ac, char **av)
{
	t_ps	*ps;
	
	if (ac > 1)
	{
		ps = init_ps();
		ps->size= ac - 1;
		make_stack_list(av, ps);
		read_instruction(ps);
		execute_instr(ps);
		show_stacks(ps);
		check_is_ok(ps);
		exit(0);
	}
	return (0);
}
