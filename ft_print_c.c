/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:00:29 by ukim              #+#    #+#             */
/*   Updated: 2020/11/22 17:40:02 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	width_zero(char c)
{
	write(1, &c, 1);
	return (1);
}

int			ft_print_c(t_flags *flag, va_list ap)
{
	char	c;
	char	*str;
	int		i;

	i = 0;
	if (!(c = va_arg(ap, int)))
		return (0);
	if (flag->width <= 0)
		return (width_zero(c));
	if (!(str = (char*)malloc(sizeof(char) * flag->width + 1)))
		return (0);
	while (i < flag->width)
		str[i++] = ' ';
	if (flag->minus == 1)
		str[0] = c;
	else
		str[flag->width - 1] = c;
	str[flag->width] = '\0';
	ft_putstr(str);
	free(str);
	return (flag->width);
}
