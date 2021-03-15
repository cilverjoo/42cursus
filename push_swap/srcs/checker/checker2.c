#include "../../includes/push_swap.h"

//sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr
char 		*return_instr_if_valid(char *instr)
{
	if (ft_strcmp(instr, "sa") == 0 || ft_strcmp(instr, "sb") == 0
		|| ft_strcmp(instr, "ss") == 0 || ft_strcmp(instr, "pa") == 0
		|| ft_strcmp(instr, "pa") == 0 || ft_strcmp(instr, "ra") == 0
		|| ft_strcmp(instr, "rb") == 0 || ft_strcmp(instr, "rr") == 0
		|| ft_strcmp(instr, "rra") == 0 || ft_strcmp(instr, "rrb") == 0
		|| ft_strcmp(instr, "rrr"))
		return (instr);
	return (0);
}

int			check_valid_arg(char *str, int *num)
{
	long	ret;
	int		len;
	int		minus;
	int		i;

	i = 0;
	if (!str)
		return (0);
	minus = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -1;
		i++;
	}
	len = ft_strlen(str);
	ret = 0;
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	if (ret > 2147483647 || ret * minus < -2147483648)
		return (0);
	*num = ret * minus;
	return (1);
}

//제대로 된 숫자가 넘어오는지부터 확인할 것.
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

int			check_stack_is_sorted(t_list *stack)
{
	t_list	*head;

	head = stack;
	while (head)
	{
		if (head->next == NULL)
			break ;
		if (head->content < head->next->content)
			return (0);
		head = head->next;
	}
	return (1);
}

//입력받은 instructions를 모두 실행해보고 ok인지 확인.
int			check_is_ok(t_ps *ps)
{
	if (ps->stack_b->content == NULL && ps->stack_b->next == NULL)
	{
		if (check_stack_is_sorted(ps->stack_a))
		{
			write(1, "OK\n", 3);
			return (1);
		}
	}
	write(1, "KO\n", 3);
	return (0);
}