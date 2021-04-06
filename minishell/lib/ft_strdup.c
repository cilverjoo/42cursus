/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:49:28 by ekim              #+#    #+#             */
/*   Updated: 2021/02/21 12:37:31 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	int		len;
	char	*copy;
	int		i;

	len = 0;
	i = 0;
	if (!s1 || !*s1)
	{
		copy = (char *)malloc(sizeof(char) * 1);
		*copy = '\0';
		return (copy);
	}
	while (s1[len])
		len++;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (copy == NULL)
		return (0);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = 0x00;
	return (copy);
}
