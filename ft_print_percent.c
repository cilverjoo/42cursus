/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim </var/mail/ekim>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:07:50 by ekim              #+#    #+#             */
/*   Updated: 2020/11/23 18:14:51 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     	ft_print_percent(t_flags *flag)
{
	char	*result;
	if (flag->width > 1)
	{
		if (flag->zero == 1)
		{
			if (flag->minus == 0)
				result = ft_left_strcat("%", '0', flag->width -1);
			else
				result = ft_right_strcat("%", ' ', flag->width - 1);
		}
		else
		{
			if (flag->minus == 0)
				result = ft_left_strcat("%", ' ', flag->width - 1);
			else
				result = ft_right_strcat("%", ' ', flag->width - 1);
		}
		ft_putstr(result);
		free(result);
		return (flag->width);
	}
	ft_putstr("%");
	return (1);
}
