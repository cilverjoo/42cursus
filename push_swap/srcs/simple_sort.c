/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:24:27 by ekim              #+#    #+#             */
/*   Updated: 2021/03/22 16:57:33 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void			make_sorted_array(int *array, t_ps *ps)
{
	t_list		*stack;
	int			i;
	int			j;
	int			tmp;

	stack = ps->stack_a;
	i = 0;
	while (stack)
	{
		array[i++] = *(stack->content);
		stack = stack->next;
	}
	i = -1;
	while (++i < ps->size)
	{
		j = -1;
		while (++j < ps->size)
			if (array[i] < array[j])
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
	}
}

static void		sort_a(t_ps *ps)
{
	t_list		*s_a;
	int			max;

	max = ps->sorted_array[ps->size - 1];
	while (!check_stack_is_sorted(ps->stack_a))
	{
		s_a = ps->stack_a;
		if (*(s_a->content) == max)
			rotate_a(&ps->stack_a, 1);
		else if (*(s_a->content) > *(s_a->next->content))
			swap_a(ps->stack_a, 1);
		else if (*(s_a->next->content) == max)
			reverse_a(&ps->stack_a, 1);
	}
}

void			sort_small_list(t_ps *ps)
{
	int			pivot;
	int			cnt;

	cnt = 0;
	pivot = (ps->sorted_array)[ps->size / 2];
	while (cnt < ps->size && ps->size > 3)
	{
		if (*(ps->stack_a->content) < pivot)
			cnt += push_b(&ps->stack_b, &ps->stack_a, 1);
		else
			cnt += rotate_a(&ps->stack_a, 1);
	}
	if (ft_lstsize(ps->stack_b) >= 2)
		if (*(ps->stack_b->content) < *(ps->stack_b->next->content))
			swap_b(ps->stack_b, 1);
	sort_a(ps);
	while (ps->stack_b)
		push_a(&ps->stack_a, &ps->stack_b, 1);
	show_stacks(ps);
}
