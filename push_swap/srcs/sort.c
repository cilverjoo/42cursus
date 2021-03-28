/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:42:59 by ekim              #+#    #+#             */
/*   Updated: 2021/03/24 17:48:29 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void			move_to_b_by_pivot(t_ps *ps, int pivot1, int pivot2)
{
	t_list		*s_a;
	int			cnt;
	int			depth;

	s_a = ps->stack_a;
	cnt = 0;
	depth = 0;
	while (s_a)
		if (*(s_a->content) >= pivot1 && *(s_a->content) <= pivot2)
		{
			cnt += depth;
			get_arg_and_push_to_b(ps, depth);
			depth = 0;
			s_a = ps->stack_a;
		}
		else
		{
			depth++;
			s_a = s_a->next;
		}
	while (cnt-- > 0)
		reverse_a(&ps->stack_a, 0);
}

void			move_to_a_in_sequence(t_ps *ps, int idx1, int idx2)
{
	t_list		*s_b;
	int			depth;
	int			i;

	depth = 0;
	i = 0;
	s_b = ps->stack_b;
	while (idx1 + i <= idx2)
		if (ps->sorted_array[idx1 + i] == *(s_b->content))
		{
			get_arg_and_push_to_a(ps, depth);
			depth = 0;
			s_b = ps->stack_b;
			i++;
		}
		else
		{
			depth++;
			s_b = s_b->next;
		}
}

void			sort_big_list(t_ps *ps, int chunk_size)
{
	int			idx1;
	int			idx2;
	int			i;

	i = 1;
	idx2 = -1;
	while (!check_is_ok(ps, 0))
	{
		idx1 = idx2 + 1;
		idx2 = chunk_size * i++ - 1;
		if (idx2 <= ps->size - 1)
		{
			move_to_b_by_pivot(ps, ps->sorted_array[idx1],
				ps->sorted_array[idx2]);
			move_to_a_in_sequence(ps, idx1, idx2);
		}
		else
		{
			idx2 = ps->size - 1;
			sort_args_small_than_chunk(ps, idx1, idx2);
		}
	}
}

int				do_sorting(t_ps *ps)
{
	int			chunk;

	if (check_is_ok(ps, 0))
		return (1);
	make_sorted_array(ps->sorted_array, ps);
	if (!check_double(ps))
		exit_program();
	if (ps->size <= 5)
		sort_small_list(ps);
	else
	{
		chunk = get_chunk_size(ps);
		sort_big_list(ps, chunk);
	}
	return (1);
}
