/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:46 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/18 00:37:07 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

//from top of stack2 to top of stack1
int			push(t_list **stack_1, t_list **stack_2)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*s_2;

	s_2 = *stack_2;
	if (s_2->content)
	{
		new = ft_lstnew(s_2->content);
		ft_lstadd_front(stack_1, new);
		if (!s_2->next)
			s_2->content = NULL;
		else
		{
			tmp = s_2->next;
			s_2->content = NULL;
			s_2->next = NULL;
			free(s_2);
			*stack_2 = tmp;
		}

		// t_list *s_1 = *stack_1;
		// while (s_1)
		// {
		// 	printf("%s\n", (char *)s_1->content);
		// 	s_1 = s_1->next;
		// }

		return (1);
	}
	return (0);
}