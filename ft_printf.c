/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:35:44 by ukim              #+#    #+#             */
/*   Updated: 2020/11/24 21:00:27 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					g_len = 0;
char				*g_base_10 = "0123456789";
char				*g_base_x = "0123456789abcdef";

static char			is_option(char *fm)
{
	if (*fm == 'c' || *fm == 's' || *fm == 'i'
			|| *fm == 'd' || *fm == 'u' || *fm == 'x'
			|| *fm == 'X' || *fm == 'p' || *fm == '%')
		return (*fm);
	return (0);
}

static int			do_op(t_flags *flag, char *fm, va_list ap)
{
	char			c;

	if (!(c = is_option(fm)))
		return (0);
	if (c == 'c')
		g_len += ft_print_c(flag, ap);
	else if (c == 'd' || c == 'i')
		g_len += ft_print_digit(flag, ap);
	else if (c == 'u')
		g_len += ft_print_ux(flag, ap, g_base_10, 0);
	else if (c == 'x')
		g_len += ft_print_ux(flag, ap, g_base_x, 0);
	else if (c == 'X')
		g_len += ft_print_ux(flag, ap, g_base_x, 1);
	else if (c == 'p')
		g_len += ft_print_point(flag, ap);
	else if (c == 's')
		g_len += ft_print_str(flag, ap);
	else if (c == '%')
		g_len += ft_print_percent(flag);
	return (0);
}

static void			zero_minus(t_flags *fg, char **sv)
{
	while (**sv == '-' || **sv == '0')
	{
		if (**sv == '-')
		{
			fg->minus = 1;
			(*sv)++;
		}
		else if (**sv == '0')
		{
			fg->zero = 1;
			(*sv)++;
		}
	}
}

int					ft_printf(const char *format, ...)
{
	char			*save;
	t_flags			flag;
	va_list			ap;

	g_len = 0;
	va_start(ap, format);
	save = (char *)format;
	while (*save)
	{
		if (*save++ == '%')
		{
			init_flag(&flag);
			zero_minus(&flag, &save);
			set_flag(&flag, &save, ap);
			do_op(&flag, save, ap);
		}
		else
		{
			write(1, save, 1);
			g_len++;
		}
	}
	va_end(ap);
	return (g_len);
}
