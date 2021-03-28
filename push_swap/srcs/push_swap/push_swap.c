/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:37 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/24 17:30:14 by ekim             ###   ########.fr       */
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
		do_sorting(ps);
	}
	return (0);
}
