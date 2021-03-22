#include "../includes/push_swap.h"

//quick sort!

void	rotate_remains(int remains, t_ps *ps)
{
	int	i;

	i = 0;
	while (i++ < remains)
		rotate_a(&ps->stack_a, 1);
}

void		move_chunk_to_b_and_reverse(int chunk_size, t_ps *ps)
{
	int		i;

	i = 0;
	while (i < chunk_size)
	{
		push_b(&ps->stack_b, &ps->stack_a, 1);
		if (i != 0)
			reverse_b(&ps->stack_b, 1);
		i++;
	}
}

//chunk_size를 줬을 때 정렬해주기.
void		merge_sort(int chunk_size, t_ps *ps)
{
	t_list	*s1;
	t_list	*s2;
	int		to_bottom;
	int		remains;

	to_bottom = 0;
	remains = ps->size;
	while (remains >= chunk_size)
	{
		move_chunk_to_b_and_reverse(chunk_size, ps);
		s1 = ps->stack_a;
		s2 = ps->stack_b;
		to_bottom = 0;
		while (to_bottom < chunk_size * 2)
		{
			//stack b가 비었거나, stack_a top < stack_b top
			if (s2->content == NULL || s1->content < s2->content)
				rotate_a(&ps->stack_a, 1);
			else
			{
				push_a(&ps->stack_a, &ps->stack_b, 1);
				rotate_a(&ps->stack_a, 1);
				s2 = ps->stack_b;
			}
			s1 = ps->stack_a;
			to_bottom++;
		}
		remains -= to_bottom;
	}
}

void		swap_top_at_start(t_ps *ps)
{
	t_list	*first;
	t_list	*second;
	int		cnt;

	//이 함수에 들어온다면 무조건 first, second는 존재하는 걸로 가정.
	cnt = 0;
	first = ps->stack_a;
	second = ps->stack_a->next;
	while (cnt < ps->size)
	{
		if (first->content > second->content)
			swap_a(ps->stack_a, 1);
		cnt += rotate_a(&ps->stack_a, 1);
		cnt += rotate_a(&ps->stack_a, 1);
		first = ps->stack_a;
		second = first->next;
	}
}

int		do_sorting(t_ps *ps)
{
	int chunk_size;

	if (check_is_ok(ps, 0))
		return (1);
	if (ps->size <= 5)
	{
		sort_small_list(ps);
		return (1);
	}
	chunk_size = 1;
	while (!ps->is_sorted)
	{
		if (chunk_size == 1)
			swap_top_at_start(ps);
		else
			merge_sort(chunk_size, ps);	
		chunk_size *= 2;
		show_stacks(ps);
		if (chunk_size >= ps->size)
			ps->is_sorted = 1;
	}
	return (1);
}

// chunk_size만큼만 stack_a에서 빼서 정렬하는 함수.
// 크기별로 chunk 안에서 idx를 부여하고 그 순서별로 stack_a의 top에 오게 하자.
// void	get_chunk_size_and_merge_sort(int chunk_size, t_ps *ps)
// {
// 	int	c1_idx;
// 	int c1_num;
// 	int c2_idx;
// 	int c2_num;
// 	int keep_list[chunk_size];
// 	int k_idx;
// 	int tmp;

// 	c1_idx = 1;
// 	c2_idx = 1 + chunk_size;
// 	c1_num = get_value_from_stack_a(c1_idx, ps->stack_a);
// 	c2_num = get_value_from_stack_a(c2_idx, ps->stack_a);
// 	k_idx = 0;

// 	while (c1_idx < 1 + chunk_size && c2_idx < 1 + 2 * chunk_size)
// 	{
// 		if (c1_num < c2_num)
// 		{
// 			rotate(&ps->stack_a);
// 			c1_idx++;
// 		}
// 		else
// 		{
// 			tmp = *(int *)(ps->stack_a->content);
// 			keep_list[k_idx] = tmp;
// 			push(&ps->stack_b, &ps->stack_a);
// 			c2_idx++;
// 		}
// 	}
// }

//재귀함수 --> 전체 덩어리의 수가 전체의 크기(len)가 될 때 종료.
//merge_chunk의 수를 2제곱으로 늘려가면서 진행. 만약 마지막 청크의 크기가 2제곱보다 작다면?
// ==> 전체 갯수가 홀수일때 / 2제곱 쌍이 안맞을 때 / 2제곱 쌍일 때.
// //몇 번째인지 입력하면 stack_a의 값을 가져온다.
// int			get_value_from_stack(int idx, t_list *stack)
// {
// 	int		i;
// 	int		num;
// 	t_list	*s;

// 	i = 0;
// 	s = stack;
// 	while (i < idx && s->content)
// 	{
// 		s = s->next;
// 		i++;
// 	}
// 	num = *(int *)(s->content);
// 	return (num);
// }
