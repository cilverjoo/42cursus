/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:43 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/22 12:50:16 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_instr		*new_instr_node(char *instr)
{
	t_instr	*new;

	new = (t_instr *)malloc(sizeof(t_instr));
	new->content = instr;
	new->next = NULL;
	return (new);
}

void		instr_add_back(t_instr **lst, t_instr *new)
{
	t_instr	*tmp;

	tmp = *lst;
	if (!(*lst))
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void		read_instruction(t_ps *ps)
{
	char	*instruction;
	int		check;
	t_instr	*new;
	t_instr	*head;

	head = ps->instr;
	while ((check = get_next_line(0, &instruction)) > 0)
	{
		if (!check_instr_valid(instruction))
			exit_program();
		if (!ps->instr)
		{
			new = new_instr_node(instruction);
			ps->instr = new;
		}
		else
		{
			new = new_instr_node(instruction);
			instr_add_back(&ps->instr, new);
		}
	}
}

int			execute_instr(t_ps *ps, char *content)
{
	if (ft_strncmp(content, "sa", 2) == 0)
		swap_a(ps->stack_a, 0);
	else if (ft_strncmp(content, "sb", 2) == 0)
		swap_b(ps->stack_b, 0);
	else if (ft_strncmp(content, "ss", 2) == 0)
		swap_both(ps, 0);
	else if (ft_strncmp(content, "pa", 2) == 0)
		push_a(&ps->stack_a, &ps->stack_b, 0);
	else if (ft_strncmp(content, "pb", 2) == 0)
		push_b(&ps->stack_b, &ps->stack_a, 0);
	else if (ft_strncmp(content, "rra", 3) == 0)
		reverse_a(&ps->stack_a, 0);
	else if (ft_strncmp(content, "rrb", 3) == 0)
		reverse_b(&ps->stack_b, 0);
	else if (ft_strncmp(content, "rrr", 3) == 0)
		reverse_both(ps, 0);
	else if (ft_strncmp(content, "ra", 2) == 0)
		rotate_a(&ps->stack_a, 0);
	else if (ft_strncmp(content, "rb", 2) == 0)
		rotate_b(&ps->stack_b, 0);
	else if (ft_strncmp(content, "rr", 2) == 0)
		rotate_both(ps, 0);
	else
		return (0);
	return (1);
}

int			execute_instrs(t_ps *ps)
{
	t_instr	*head;

	head = ps->instr;
	while (head)
	{
		if (!(execute_instr(ps, head->content)))
			return (0);
		head = head->next;
	}
	return (1);
}
