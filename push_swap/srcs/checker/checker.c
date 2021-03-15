// 중복, 숫자가 아닌 것, 정수 범위를 넘어서면 ==> error
// 첫 번째 값이 index 0, 1, ...
// 아무것도 입력받지 않으면 아무 반응 없음.
// stack을 읽고, 명령어 (ra, pb, sa 등)를 입력받아서 stack a가 정렬이 되고 stack b가 비어있으면 ok 출력.
// 다른 경우 "KO\n" (gnl 오류)

#include "../../includes/push_swap.h"

int			make_stack_list(char **av, t_ps *ps)
{
	int		i;
	int		num;
	t_list	*head;
	t_list	*new;

	i = 1;
	head = ps->stack_a;
	while (i < ps->len)
	{
		if (check_valid_arg(av[i], &num))
		{
			new = ft_lstnew(av[i]);
			ft_lstadd_back(&head, new);
			head = head->next;
		}
		else
			return (exit_program());
		i++;
	}
	return (1);
}

void		read_instruction(t_ps *ps)
{
	char	*instruction;
	t_list	*new;
	t_list	*head;

	head = &ps->instr;
	while (get_next_line(0, &instruction))
	{
		//signal check
		if (!return_instr_if_valid(instruction))
			return (exit_program());
		new = ft_lstnew(instruction);
		ft_lstadd_back(&head, new);
		head = head->next;
	}
}

//instr 리스트에서 NULL을 만날때까지 instr 실행하라.
//sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr
int			execute_instr(t_ps *ps)
{
	t_list	*head;

	head = ps->instr;
	while (head)
	{
		if (ft_strcmp(head->content, "sa") == 0)
			return (swap_a(ps->stack_a));
		if (ft_strcmp(head->content, "sb") == 0)
			return (swap_b(ps->stack_b));
		if (ft_strcmp(head->content, "ss") == 0)
			return (swap_both(ps));
		if (ft_strcmp(head->content, "pa") == 0)
			return (push_a(ps->stack_a, ps->stack_b));
		if (ft_strcmp(head->content, "pb") == 0)
			return (push_b(ps->stack_b, ps->stack_a));
		if (ft_strcmp(head->content, "ra") == 0)
			return (rotate_a(ps->stack_a));
		if (ft_strcmp(head->content, "rb") == 0)
			return (rotate_b(ps->stack_b));
		if (ft_strcmp(head->content, "rr") == 0)
			return (rotate_both(ps));
		if (ft_strcmp(head->content, "rra") == 0)
			return (reverse_rotate_a(ps->stack_a));
		if (ft_strcmp(head->content, "rrb") == 0)
			return (reverse_rotate_b(ps->stack_b));
		if (ft_strcmp(head->content, "rrr") == 0)
			return (reverse_rotate_both(ps));
	}
}

//av -> 유효성체크 -> int 변환해서 stack_a, stack_b에 넣어주기
//gnl을 통해서 입력받을 수 있게.
//ctrl + D 시그널 입력받으면 --> s_A의 정렬상태 확인, stack_b의 정렬상태 확인.
int			main(int ac, char **av)
{
	t_ps	ps;
	char	*instruction;
	t_list	*new;
	t_list	*head;

	if (ac > 1)
	{
		head = ps.instr;
		ps.len = ac;
		init_stack(&ps);
		make_stack_list(av, &ps);
		read_instruction(&ps);
		execute_instr(&ps);
		check_is_ok(&ps);
	}
	return (0);
}