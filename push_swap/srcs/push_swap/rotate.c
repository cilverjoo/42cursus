#include "../../includes/push_swap.h"

int			rotate(t_list *stack)
{
	t_list	*head;
	t_list	*tail;
	void	*tmp;
	void	*last;

	head = stack;
	if (ft_lstsize(head) <= 1)
		return (0);
	if (head)
	{
		tail = ft_lstnew(head->content);
		ft_lstadd_back(&head, tail);
		head->content = NULL;
		head->next = NULL;
		free(head);
		head = NULL;
	}
	return (1);
}

int			rotate_both(t_ps *ps)
{
	if (!rotate(ps->stack_a) || !rotate(ps->stack_b))
		return (0);
	return (1);
}