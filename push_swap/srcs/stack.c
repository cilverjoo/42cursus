/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:53 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/18 15:19:59 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

//content free 필요!
int			make_stack_list(char **av, t_ps *ps)
{
	int		i;
	int		*ptr;
	t_list	*new;
	t_list	*head;

	i = 1;
	head = ps->stack_a;
	while (i < ps->len)
	{
		ptr = (int *)malloc(sizeof(int));
		if (check_valid_arg(av[i], ptr))
		{
			if (!head->content)
				head->content = ptr;
			else
			{
				new = ft_lstnew(ptr);
				ft_lstadd_back(&head, new);
			}
		}
		else
			return (exit_program());
		i++;
	}
	// while (head)
	// {
	// 	printf("%d\n", *(int *)head->content);
	// 	head = head->next;
	// }
	return (1);
}

int			check_stack_is_sorted(t_list *stack)
{
	t_list	*head;
	int		*num1;
	int		*num2;

	head = stack;
	while (head)
	{
		if (!head->next || !head->content)
			break ;
		num1 = head->content;
		num2 = head->next->content;
		if (*num1 > *num2)
			return (0);
		head = head->next;
	}
	return (1);
}

int			check_is_ok(t_ps *ps)
{
	if (ps->stack_b->content || !check_stack_is_sorted(ps->stack_a))
	{
		write(1, "KO\n", 3);
		return (0);
	}
	write(1, "OK\n", 3);
	return (1);
}