#include "../../includes/push_swap.h"

int			reverse(t_list *stack)
{
	t_list	*head;
	t_list	*tail;
	t_list	*tmp;

	head = stack;
	if (ft_lstsize(head) <= 1)
		return (0);
	while (head->next)
	{
		if (!head->next->next)
		{
			tail = ft_lstnew(head->next->content);
			ft_lstadd_front(&head, tail);
			tmp = head->next;
			tmp->content = NULL;
			free(tmp);
			tmp = NULL;
			head->next = NULL;
			return (1);
		}
	}
	return (0);
}

int			reverse_both(t_ps *ps)
{
	if (!reverse(ps->stack_b) || !reverse(ps->stack_b))
		return (0);
	return (1);
}