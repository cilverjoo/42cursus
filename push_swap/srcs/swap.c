/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:55 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/18 15:20:08 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			swap(t_list *stack)
{
	t_list	*top;
	void	*tmp;

	top = stack;
	if (top)
	{
		if (!top->content || !top->next || !top->next->content)
			return (0);
		tmp = top->content;
		top->content = top->next->content;
		top->next->content = tmp;
		return (1);
	}
	return (0);
}

int			swap_both(t_ps *ps)
{
	return (swap(ps->stack_a) && swap(ps->stack_b));	
}