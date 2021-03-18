/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:40 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/18 15:26:33 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			check_valid_arg(char *str, int *ptr)
{
	long	ret;
	int		len;
	int		minus;
	int		i;
	int		num;

	i = 0;
	minus = 1;
	len = (int)ft_strlen(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	ret = 0;
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	if (ret > 2147483647 || ret * minus < -2147483648)
		return (0);
	num = (int)(ret * minus);
	*ptr = num;
	return (1);
}