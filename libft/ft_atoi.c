/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:26:59 by ekim              #+#    #+#             */
/*   Updated: 2021/03/15 14:23:48 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_isspace(char c)
{
	if (c == '\v' || c == '\n' || c == '\t' ||
			c == '\r' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int					ft_atoi(const char *str)
{
	int				i;
	int				minus;
	long			result;

	i = 0;
	minus = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (i > 19 || result >= 9223372036854775808ULL)
		return (minus == 1 ? -1 : 0);
	return (minus * result);
}
