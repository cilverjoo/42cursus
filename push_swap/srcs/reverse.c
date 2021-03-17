/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:48 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/18 01:09:25 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			reverse(t_list **stack)
{
	t_list	*head;
	t_list	*tail;
	t_list	*tmp;

	head = *stack;
	while (head->next)
	{
		if (!head->next->next)
		{
			tail = ft_lstnew(head->next->content);
			ft_lstadd_front(stack, tail);
			tmp = head->next;
			free(tmp);
			tmp = NULL;
			head->next = NULL;
			return (1);
		}
		head = head->next;
	}
	// t_list *tmp2;
	// tmp2 = *stack;
	// while (tmp2)
	// {
	// 	printf("reverse : %d\n", *(int*)tmp2->content);
	// 	tmp2 = tmp2->next;
	// }
	return (0);
}

int			reverse_both(t_ps *ps)
{
	return (reverse(&ps->stack_b) && reverse(&ps->stack_b));
}