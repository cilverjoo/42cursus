/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 02:52:26 by ekim              #+#    #+#             */
/*   Updated: 2020/10/18 14:56:49 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;

	if (!(*f) || !lst)
		return (NULL);
	if (!(new = ft_lstnew((*f)(lst->content))))
		return (NULL);
	head = new;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new->next = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&head, (*del));
			return (NULL);
		}
		new = new->next;
	}
	return (head);
}
