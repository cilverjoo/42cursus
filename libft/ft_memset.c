/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:01:14 by ekim              #+#    #+#             */
/*   Updated: 2020/10/07 19:17:57 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*s;

	s = (unsigned char *)str;
	while (len--)
		*s++ = (unsigned char)c;
	return (str);
}
