/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:11:00 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/24 17:49:21 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			check_double(t_ps *ps)
{
	int		i;

	i = 0;
	while (i < ps->size - 1)
	{
		if (ps->sorted_array[i] == ps->sorted_array[i + 1])
			return (0);
		i++;
	}
	return (1);
}

t_ps		*init_ps(int size)
{
	t_ps	*ps;

	ps = (t_ps *)malloc(sizeof(t_ps));
	ps->size = size;
	if (!(ps->sorted_array = (int *)malloc(sizeof(int) * size)))
		return (NULL);
	ps->stack_a = NULL;
	ps->stack_b = NULL;
	ps->instr = NULL;
	ps->p_instr = NULL;
	return (ps);
}

int			clear_all(t_ps *ps)
{
	t_list	*list;
	t_list	*tmp;

	list = ps->stack_a;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
	list = ps->stack_b;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
	free(ps);
	return (1);
}

int			exit_program(void)
{
	char	*error;

	error = "Error\n";
	write(2, error, 6);
	exit(0);
}

int			get_chunk_size(t_ps *ps)
{
	if (ps->size <= 10)
		return (3);
	else if (ps->size <= 20)
		return (5);
	else if (ps->size <= 50)
		return (10);
	else if (ps->size <= 100)
		return (20);
	else if (ps->size <= 200)
		return (30);
	return (50);
}
