/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:48 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/21 15:06:39 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			reverse_a(t_list **stack, int check)
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
			head->prev = NULL;
			break ;
		}
		head = head->next;
	}
	if (check)
		write(1, "rra\n", 4);
	return (0);
}

int			reverse_b(t_list **stack, int check)
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
			head->prev = NULL;
			break ;
		}
		head = head->next;
	}
	if (check)
		write(1, "rrb\n", 4);
	return (0);
}

int			reverse_both(t_ps *ps, int check)
{
	int		a;
	int		b;

	a = reverse_a(&ps->stack_b, 0);
	b = reverse_b(&ps->stack_b, 0);
	if (check)
		write(1, "rrr\n", 4);
	return (a & b);
}