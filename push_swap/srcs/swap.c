/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:55 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/22 12:50:58 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			swap_a(t_list *stack, int check)
{
	t_list	*top;
	int		*tmp;

	top = stack;
	if (!top || !top->next)
		return (0);
	tmp = top->content;
	top->content = top->next->content;
	top->next->content = tmp;
	if (check)
		write(1, "sa\n", 3);
	return (1);
}

int			swap_b(t_list *stack, int check)
{
	t_list	*top;
	int		*tmp;

	top = stack;
	if (!top || !top->next)
		return (0);
	tmp = top->content;
	top->content = top->next->content;
	top->next->content = tmp;
	if (check)
		write(1, "sb\n", 3);
	return (1);
}

int			swap_both(t_ps *ps, int check)
{
	int		a;
	int		b;

	a = swap_a(ps->stack_a, 0);
	b = swap_b(ps->stack_b, 0);
	if (check)
		write(1, "ss\n", 3);
	return (a & b);
}
