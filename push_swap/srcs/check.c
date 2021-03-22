/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:40 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/21 15:34:42 by kim-eunju        ###   ########.fr       */
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

int			check_is_ok(t_ps *ps, int check)
{
	if (ps->stack_b || !check_stack_is_sorted(ps->stack_a))
	{
		if (check == 1)
			write(1, "KO\n", 3);
		return (0);
	}
	if (check == 1)
		write(1, "OK\n", 3);
	return (1);
}