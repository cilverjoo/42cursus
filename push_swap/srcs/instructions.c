/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:43 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/18 16:35:17 by kim-eunju        ###   ########.fr       */
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

int			execute_instr(t_ps *ps)
{
	t_list	*head;

	head = ps->instr;
	while (head)
	{
		if (ft_strncmp(head->content, "sa", 2) == 0)
			swap(ps->stack_a);
		else if (ft_strncmp(head->content, "sb", 2) == 0)
			swap(ps->stack_b);
		else if (ft_strncmp(head->content, "ss", 2) == 0)
			swap_both(ps);
		else if (ft_strncmp(head->content, "pa", 2) == 0)
			push(&ps->stack_a, &ps->stack_b);
		else if (ft_strncmp(head->content, "pb", 2) == 0)
			push(&ps->stack_b, &ps->stack_a);
		else if (ft_strncmp(head->content, "rra", 3) == 0)
			reverse(&ps->stack_a);
		else if (ft_strncmp(head->content, "rrb", 3) == 0)
			reverse(&ps->stack_b);
		else if (ft_strncmp(head->content, "rrr", 3) == 0)
			reverse_both(ps);
		else if (ft_strncmp(head->content, "ra", 2) == 0)
			rotate(&ps->stack_a);
		else if (ft_strncmp(head->content, "rb", 2) == 0)
			rotate(&ps->stack_b);
		else if (ft_strncmp(head->content, "rr", 2) == 0)
			rotate_both(ps);
		else
			return (0);
		head = head->next;
	}
	return (1);
}

int 		check_instr_valid(char *instr)
{
	if (ft_strncmp(instr, "sa", 2) == 0 || ft_strncmp(instr, "sb", 2) == 0
		|| ft_strncmp(instr, "ss", 2) == 0 || ft_strncmp(instr, "pa", 2) == 0
		|| ft_strncmp(instr, "pb", 2) == 0 || ft_strncmp(instr, "ra", 2) == 0
		|| ft_strncmp(instr, "rb", 2) == 0 || ft_strncmp(instr, "rr", 2) == 0
		|| ft_strncmp(instr, "rra", 3) == 0 || ft_strncmp(instr, "rrb", 3) == 0
		|| ft_strncmp(instr, "rrr", 3) == 0)
		return (1);
	return (0);
}

void		read_instruction(t_ps *ps)
{
	char	*instruction;
	int		check;
	t_list	*new;
	t_list	*head;

	head = ps->instr;
	while ((check = get_next_line(0, &instruction)) > 0)
	{
		if (!check_instr_valid(instruction))
			exit_program();
		if (!ps->instr->content)
			ps->instr->content = instruction;
		else
		{
			new = ft_lstnew(instruction);
			ft_lstadd_back(&ps->instr, new);
		}
	}
}
