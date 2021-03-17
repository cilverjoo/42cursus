/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:52:06 by ekim              #+#    #+#             */
/*   Updated: 2020/10/09 20:27:33 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		tmp;

	i = 0;
	j = ft_strlen(dst);
	tmp = j;
	if (size > 0 && j < size)
	{
		while (src[i] && j + 1 < size)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = 0x00;
		return (tmp + ft_strlen(src));
	}
	return (size + ft_strlen(src));
}
