/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:53 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/24 17:38:07 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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
		else
			return (exit_program());
		i++;
	}
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

void		show_stacks(t_ps *ps)
{
	t_list	*s_1;
	t_list	*s_2;

	s_1 = ps->stack_a;
	s_2 = ps->stack_b;
	printf("\n\n\n**************start**************\n");
	while (1)
	{
		if (s_1)
			printf("%8d", *s_1->content);
		else
			printf("        ");
		if (s_2)
			printf("%10d", *s_2->content);
		printf("\n");
		if (!s_1 && !s_2)
			break ;
		if (s_1)
			s_1 = s_1->next;
		if (s_2)
			s_2 = s_2->next;
	}
	printf("     stackA     stackB");
	printf("\n**************end****************\n\n\n");
}
