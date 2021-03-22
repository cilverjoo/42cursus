/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:51 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/21 14:25:27 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			rotate_a(t_list **stack, int check)
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
	if (check)
		write(1, "ra\n", 3);
	return (1);
}

int			rotate_b(t_list **stack, int check)
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
	if (check)
		write(1, "rb\n", 3);
	return (1);
}

int			rotate_both(t_ps *ps, int check)
{
	int		a;
	int		b;

	a = rotate_a(&ps->stack_a, 0);
	b = rotate_b(&ps->stack_b, 0);
	if (check)
		write(1, "rr\n", 3);
	return (a & b);
}