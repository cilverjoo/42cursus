
#include "../../includes/push_swap.h"

//change first to second.
int			swap(t_list *stack)
{
	t_list	*top;
	int		tmp;

	top = stack;
	if (top)
	{
		if (!top->content || !top->next || !top->next->content)
			return (0);
		tmp = (int)top->content;
		top->content = top->next->content;
		top->next->content = tmp;
		return (1);
	}
	return (0);
}

int			swap_both(t_ps *ps)
{
	if (!swap(ps->stack_a) || !swap(ps->stack_b))
		return (0);
	return (1);	
}