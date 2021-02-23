/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 01:01:43 by heryu             #+#    #+#             */
/*   Updated: 2021/02/08 20:04:17 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_my_strchr(char *str, char chr)
{
	size_t	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == chr)
			return (str + i);
		i++;
	}
	return (NULL);
}

void		ft_strncpy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char		*ft_strncat_and_free(char *dst, char *src, size_t size)
{
	char	*ret;
	size_t	dst_size;

	dst_size = (dst == NULL) ? 0 : ft_strlen(dst);
	if ((ret = (char *)malloc((dst_size + size + 1) * sizeof(char))) == NULL)
	{
		free(dst);
		return (NULL);
	}
	ft_strncpy(ret, dst, dst_size);
	ft_strncpy(ret + dst_size, src, size);
	ret[dst_size + size] = '\0';
	if (dst != NULL)
		free(dst);
	return (ret);
}
