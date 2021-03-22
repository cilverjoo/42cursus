#include "../includes/push_swap.h"

void		move_to_b_by_pivot(t_ps *ps, int pivot1, int pivot2)
{
	t_list	*s_a;
	int		cnt;
	int		depth;

	s_a = ps->stack_a;
	while (s_a)
		if (*(s_a->content) <= pivot2 && *(s_a->content) > pivot1)
		{
			if (depth < ps->size / 2)
			{
				cnt = depth;
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

void		move_to_a_in_sequence(t_ps *ps, int j, int idx)
{
	t_list	*s_b;
	int		depth;

	depth = 0;
	s_b = ps->stack_b;
	while (j <= idx)
		if (ps->sorted_array[j] == *(s_b->content))
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
			j++;
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
	while ((*stack->content) > pivot1)
	{
		push_b(&ps->stack_b, &ps->stack_a, 1);
		stack = ps->stack_a;
	}
	move_to_a_in_sequence(ps, start, end);
}

void		sort_big_list(t_ps *ps, int chunk_size)
{
	int		pivot1;
	int		pivot2;
	int		idx;
	int		i;
	int		j;

	i = 1;
	pivot1 = 0;
	pivot2 = 0;
	while (!check_is_ok(ps, 0))
	{
		if (pivot2 != 0)
			pivot1 = pivot2;
		idx = chunk_size * i - 1;
		printf("size : %d idx : %d\n", ps->size, idx);
		if (idx < ps->size - 1)
		{
			pivot2 = (ps->sorted_array)[idx];
			move_to_b_by_pivot(ps, pivot1, pivot2);
			show_stacks(ps);
			j = chunk_size * (i - 1);
			move_to_a_in_sequence(ps, j, idx);
		}
		else if (idx > ps->size - 1)
		{
			printf("bigger\n");
			idx = ps->size - 1;
			printf("pivot1 : %d start : %d\n", pivot1, chunk_size * (i - 1));
			// pivot2 = (ps->sorted_array)[idx];
			sort_args_small_than_chunk(ps, pivot1, chunk_size * (i - 1), idx);
		}
		else
			rotate_a(&ps->stack_a, 1); //남은 인자가 하나밖에 없을 때.
		i++;
		printf("pivot1 : %d pivot2 : %d\n", pivot1, pivot2);
		sleep(1);
		show_stacks(ps);
	}
}

int			do_sorting(t_ps *ps)
{
	if (check_is_ok(ps, 0))
		return (1);
	make_sorted_array(ps->sorted_array, ps);
	if (ps->size <= 5)
		sort_small_list(ps);
	else
		sort_big_list(ps, 5);
	return (1);
} 
