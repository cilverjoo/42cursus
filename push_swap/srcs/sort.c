#include "../includes/push_swap.h"

void	move_top_chunk_to_b(int chunk_size, t_ps *ps)
{
	int		i;

	i = 0;
	while (i < chunk_size)
	{
		push(&ps->stack_b, &ps->stack_a);
		i++;
	}
}

void		merge_sort(int chunk_size, t_ps *ps)
{
	t_list *s1;
	t_list *s2;
	int		to_bottom;

	to_bottom = 0;
	move_top_chunk_to_b(chunk_size, ps);
	s1 = ps->stack_a;
	s2 = ft_lstlast(ps->stack_b);
	//chunk_size = this.
	while (to_bottom < chunk_size * 2)
	{
		
	}

}

int		sorting(t_ps *ps)
{
	int chunk_size;
	int tmp1;
	int	tmp2;

	chunk_size = 2;
	if (ps->len <= 2)
	{
		if (!check_stack_is_sorted(ps->stack_a))
			swap(ps->stack_a);
		return (1);
	}
	while (!ps->is_sorted)
	{
		merge_sort(chunk_size, ps);
		chunk_size *= 2;
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
