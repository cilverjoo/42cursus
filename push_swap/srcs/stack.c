/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:53 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/21 17:48:18 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

//content free 필요!
int			make_stack_list(char **av, t_ps *ps)
{
	int		i;
	int		*ptr;
	t_list	*new;

	i = 1;
	while (i <= ps->size)
	{
		ptr = (int *)malloc(sizeof(int));
		if (check_valid_arg(av[i], ptr))
		{
			if (!ps->stack_a)
			{
				new = ft_lstnew(ptr);
				ps->stack_a = new;
			}
			else
			{
				new = ft_lstnew(ptr);
				ft_lstadd_back(&ps->stack_a, new);
			}
		}
		else
			return (exit_program());
		i++;
	}
	show_stacks(ps);
	return (1);
}

int			check_stack_is_sorted(t_list *stack)
{
	t_list	*head;
	int		*num1;
	int		*num2;

	head = stack;
	while (head && head->next)
	{
		num1 = head->content;
		num2 = head->next->content;
		if (*num1 > *num2)
			return (0);
		head = head->next;
	}
	return (1);
}
