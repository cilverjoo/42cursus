/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:32:16 by ekim              #+#    #+#             */
/*   Updated: 2020/10/14 17:02:12 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	find_len;

	i = 0;
	if (!*to_find)
		return ((char *)str);
	find_len = ft_strlen(to_find);
	while (str[i] && i + find_len <= len)
	{
		if (str[i] == to_find[0])
		{
			if (ft_strncmp(str + i, to_find, find_len) == 0)
				return ((char *)(str + i));
		}
		i++;
	}
	return (0);
}
