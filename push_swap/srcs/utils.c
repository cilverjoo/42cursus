/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:11:00 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/21 16:24:03 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_ps		*init_ps(void)
{
	t_ps	*ps;
	
	ps = (t_ps *)malloc(sizeof(t_ps));
	ps->size = 0;
	ps->is_sorted = 0;
	ps->stack_a = NULL;
	ps->stack_b = NULL;
	ps->instr = NULL;
	ps->p_instr = NULL;
	return (ps);
}

int			exit_program(void)
{
	char	*error;

	error = "Error\n";
	write(2, error, 6);
	exit(0);
}


void		show_stacks(t_ps *ps)
{
	t_list *s_1;
	t_list *s_2;

	s_1 = ps->stack_a;
	s_2 = ps->stack_b;

	printf("\n\n\n**************start**************\n");
	while (1)
	{
		if (s_1)
			printf("%8d", *s_1->content);
		else
			printf("          ");
		if (s_2)
			printf("%10d", *s_2->content);
		printf("\n");
		if (!s_1 && !s_2)
			break;
		if (s_1)
			s_1 = s_1->next;
		if (s_2)
			s_2 = s_2->next;
	}
	printf("     stackA        stackB");
	printf("\n**************end****************\n\n\n");
}
