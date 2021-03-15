#include "../../includes/push_swap.h"

int			push(t_list *stack_a, t_list *stack_b)
{
	t_list	*tmp;

	if (stack_b->content)
	{
		ft_lstadd_front(&stack_a, stack_b);
		tmp = stack_b;
		stack_b = stack_b->next;
		tmp->content = NULL;
		tmp->next = NULL;
		free(tmp);
		return (1);
	}
	return (0);
}