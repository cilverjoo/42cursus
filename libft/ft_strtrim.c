/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:52:13 by ekim              #+#    #+#             */
/*   Updated: 2020/10/14 22:46:35 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trim_check(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;
	int		idx;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	while (trim_check(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (trim_check(s1[end], set) && end > 0)
		end--;
	if (start > end)
		return (ft_strdup(""));
	if (!(result = (char *)malloc(sizeof(char) * (end - start + 2))))
		return (0);
	idx = 0;
	while (start <= end)
		result[idx++] = s1[start++];
	result[idx] = '\0';
	return (result);
}
