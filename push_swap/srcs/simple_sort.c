#include "../includes/push_swap.h"

int			*make_sorted_array(t_ps *ps)
{
	t_list	*stack;
	int		*arr;
	int		i;
	int		j;
	int		tmp;

	stack = ps->stack_a;
	arr = (int *)malloc(sizeof(int) * 5);
	i = 0;
	while (stack)
	{
		arr[i++] = *(stack->content);
		stack = stack->next;
	}
	i = -1;
	while (++i < ps->size)
	{
		j = 0;
		while (j < ps->size)
		{
			if (arr[i] < arr[j])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
	}
	return (arr);
}

static void		sort_a(t_ps *ps, int max)
{
	t_list	*s_a;

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

void		simple_sort(t_ps *ps, int *arr, int pivot)
{
	int		cnt;

	cnt = 0;
	while (cnt < ps->size && ps->size > 3)
	{
		if (*(ps->stack_a->content) < pivot)
			cnt += push_b(&ps->stack_b, &ps->stack_a, 1);
		else
			cnt += rotate_a(&ps->stack_a, 1);
	}
	if (ft_lstsize(ps->stack_b) >= 2)
		if (*(ps->stack_b->content) < *(ps->stack_b->next->content))
			swap_a(ps->stack_a, 1);
	sort_a(ps, arr[ps->size - 1]);
	while (ps->stack_b)
		push_a(&ps->stack_a, &ps->stack_b, 1);
	show_stacks(ps);
}

void		sort_small_list(t_ps *ps)
{
	int		*arr;
	int		idx;
	int		pivot;

	arr = make_sorted_array(ps);
	idx = ps->size % 2 == 1 ? ps->size / 2 : ps->size / 2 - 1;
	pivot = arr[idx];
	simple_sort(ps, arr, pivot);
}
