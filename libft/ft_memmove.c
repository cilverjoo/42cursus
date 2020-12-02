/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 20:11:33 by ekim              #+#    #+#             */
/*   Updated: 2020/10/19 19:09:08 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char			*tmp;
	const unsigned char		*s;
	size_t					i;

	tmp = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = n;
	if (!dst && !src)
		return (NULL);
	if (dst <= src)
	{
		while (n--)
			*tmp++ = *s++;
	}
	else
	{
		while (i--)
			tmp[i] = s[i];
	}
	return (dst);
}
