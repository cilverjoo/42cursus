/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:46 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/24 15:42:22 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			push_a(t_list **stack_1, t_list **stack_2, int check)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*s_2;
	int		*num;

	s_2 = *stack_2;
	if (s_2)
	{
		num = s_2->content;
		new = ft_lstnew(num);
		ft_lstadd_front(stack_1, new);
		if (!s_2->next)
			*stack_2 = NULL;
		else
		{
			tmp = s_2->next;
			*stack_2 = tmp;
		}
		s_2->content = NULL;
		free(s_2);
		s_2 = NULL;
	}
	if (check)
		write(1, "pa\n", 3);
	return (1);
}

int			push_b(t_list **stack_1, t_list **stack_2, int check)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*s_2;
	int		*num;

	s_2 = *stack_2;
	if (s_2)
	{
		num = s_2->content;
		new = ft_lstnew(num);
		ft_lstadd_front(stack_1, new);
		if (!s_2->next)
			*stack_2 = NULL;
		else
		{
			tmp = s_2->next;
			*stack_2 = tmp;
		}
		s_2->content = NULL;
		free(s_2);
		s_2 = NULL;
	}
	if (check)
		write(1, "pb\n", 3);
	return (1);
}
