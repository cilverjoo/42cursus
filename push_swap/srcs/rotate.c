/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:51 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/18 15:20:44 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			rotate(t_list **stack)
{
	t_list	*head;
	t_list	*tail;
	t_list	*next;

	head = *stack;
	if (head)
	{
		tail = ft_lstnew(head->content);
		ft_lstadd_back(stack, tail);
		next = head->next;
		*stack = next;
		head->content = NULL;
		head->next = NULL;
		head->prev = NULL;
		free(head);
		head = NULL;
	}

	// t_list *tmp;
	// tmp = *stack;
	// while (tmp)
	// {
	// 	printf("rotate : %d\n", *(int*)tmp->content);
	// 	tmp = tmp->next;
	// }
	return (1);
}

int			rotate_both(t_ps *ps)
{
	return (rotate(&ps->stack_a) && rotate(&ps->stack_b));
}