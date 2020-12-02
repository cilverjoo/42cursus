/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 17:25:58 by ekim              #+#    #+#             */
/*   Updated: 2020/10/12 22:32:48 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s2;
	unsigned char		c2;
	size_t				i;

	i = 0;
	s2 = (unsigned char*)s;
	c2 = (unsigned char)c;
	while (i < n)
	{
		if (s2[i] == c2)
			return ((char *)s2 + i);
		i++;
	}
	return (NULL);
}
