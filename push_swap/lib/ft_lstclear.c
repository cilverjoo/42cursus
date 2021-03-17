/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 01:48:26 by ekim              #+#    #+#             */
/*   Updated: 2020/10/18 14:40:33 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*next_tmp;

	if (!lst || !del)
		return ;
	next_tmp = *lst;
	while (next_tmp)
	{
		tmp = next_tmp;
		next_tmp = tmp->next;
		(*del)(tmp->content);
		free(tmp);
		tmp = 0x00;
	}
	*lst = 0x00;
}
