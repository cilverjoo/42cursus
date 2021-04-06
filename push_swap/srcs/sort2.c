/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:00:02 by ekim              #+#    #+#             */
/*   Updated: 2021/03/24 16:03:51 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void			sort_args_small_than_chunk(t_ps *ps, int idx1, int idx2)
{
	t_list		*stack;
	int			pivot1;

	if (idx1 >= idx2)
		rotate_a(&ps->stack_a, 1);
	else if (idx2 - idx1 == 1)
	{
		if (*ps->stack_a->content > *ps->stack_a->next->content)
			swap_a(ps->stack_a, 1);
		rotate_a(&ps->stack_a, 1);
		rotate_a(&ps->stack_a, 1);
	}
	else
	{
		stack = ps->stack_a;
		pivot1 = ps->sorted_array[idx1];
		while ((*stack->content) >= pivot1)
		{
			push_b(&ps->stack_b, &ps->stack_a, 1);
			stack = ps->stack_a;
		}
		move_to_a_in_sequence(ps, idx1, idx2);
	}
}

void			get_arg_and_push_to_a(t_ps *ps, int depth)
{
	if (depth <= ft_lstsize(ps->stack_b) / 2)
		while (depth-- > 0)
			rotate_b(&ps->stack_b, 1);
	else
		while (depth++ < ft_lstsize(ps->stack_b))
			reverse_b(&ps->stack_b, 1);
	push_a(&ps->stack_a, &ps->stack_b, 1);
	rotate_a(&ps->stack_a, 1);
}

void			get_arg_and_push_to_b(t_ps *ps, int depth)
{
	if (depth < ps->size / 2)
	{
		while (depth-- > 0)
			rotate_a(&ps->stack_a, 1);
	}
	else
		while (depth++ < ps->size)
			reverse_a(&ps->stack_a, 1);
	push_b(&ps->stack_b, &ps->stack_a, 1);
}
