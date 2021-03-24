#include "../includes/push_swap.h"

void		move_to_b_by_pivot(t_ps *ps, int pivot1, int pivot2)
{
	t_list	*s_a;
	int		cnt;
	int		depth;

	s_a = ps->stack_a;
	cnt = 0;
	depth = 0;
	while (s_a)
		if (*(s_a->content) >= pivot1 && *(s_a->content) <= pivot2)
		{
			if (depth < ps->size / 2)
			{
				cnt += depth;
				while (depth-- > 0)
					rotate_a(&ps->stack_a, 1);
			}
			else
				while (depth++ < ps->size)
					reverse_a(&ps->stack_a, 1);
			push_b(&ps->stack_b, &ps->stack_a, 1);
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

void		move_to_a_in_sequence(t_ps *ps, int idx1, int idx2)
{
	t_list	*s_b;
	int		depth;
	int		i;

	depth = 0;
	i = 0;
	s_b = ps->stack_b;
	while (idx1 + i <= idx2)
		if (ps->sorted_array[idx1 + i] == *(s_b->content))
		{
			if (depth <= ft_lstsize(ps->stack_b) / 2)
				while (depth-- > 0)
					rotate_b(&ps->stack_b, 1);
			else
				while (depth++ < ft_lstsize(ps->stack_b))
					reverse_b(&ps->stack_b, 1);
			push_a(&ps->stack_a, &ps->stack_b, 1);
			rotate_a(&ps->stack_a, 1);
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

void		sort_args_small_than_chunk(t_ps *ps, int pivot1, int start, int end)
{
	t_list	*stack;

	stack = ps->stack_a;
	while ((*stack->content) >= pivot1)
	{
		push_b(&ps->stack_b, &ps->stack_a, 1);
		stack = ps->stack_a;
	}
	// show_stacks(ps);
	move_to_a_in_sequence(ps, start, end);
	// show_stacks(ps);
}

void		sort_big_list(t_ps *ps, int chunk_size)
{
	int		idx1;
	int		idx2;
	int		i;

	i = 1;
	idx2 = -1;
	while (!check_is_ok(ps, 0))
	{
		idx1 = idx2 + 1;
		idx2 = chunk_size * i - 1;
		// printf("idx1: %d idx2 : %d\n", idx1, idx2);
		if (idx2 <= ps->size - 1)
		{
			// printf("pivot1 : %d pivot2 : %d\n", ps->sorted_array[idx1], ps->sorted_array[idx2]);
			move_to_b_by_pivot(ps, ps->sorted_array[idx1], ps->sorted_array[idx2]);
			// show_stacks(ps);
			move_to_a_in_sequence(ps, idx1, idx2);
		}
		else
		{
			idx2 = ps->size - 1;
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
				sort_args_small_than_chunk(ps, ps->sorted_array[idx1], idx1, idx2);
		}
		i++;
		// show_stacks(ps);
	}
}

int			get_chunk_size(t_ps *ps)
{
	if (ps->size <= 10)
		return (3);
	else if (ps->size <= 20)
		return (5);
	else if (ps->size <= 50)
		return (10);
	else if (ps->size <= 100)
		return (20);
	else if (ps->size <= 200)
		return (25);
	else
		return (30);	
}

int			do_sorting(t_ps *ps)
{
	int		chunk;

	if (check_is_ok(ps, 0))
		return (1);
	make_sorted_array(ps->sorted_array, ps);
	if (ps->size <= 5)
		sort_small_list(ps);
	else
	{
		chunk = get_chunk_size(ps);	
		sort_big_list(ps, chunk);
	}
	// show_stacks(ps);
	return (1);
}