/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:26:59 by ekim              #+#    #+#             */
/*   Updated: 2020/11/24 20:41:14 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_atoi(char **str)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign *= -1;
		(*str)++;
	}
	while (**str && ft_isdigit(**str))
	{
		num *= 10;
		num += **str - '0';
		(*str)++;
	}
	return (sign * num);
}
