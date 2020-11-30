/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 18:59:30 by ekim              #+#    #+#             */
/*   Updated: 2020/11/27 20:31:21 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_free_strjoin(char *s1, char *s2)
{
	char		*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}

static void		add_space(char **istr, t_flags *fg)
{
	int			x;

	x = fg->width - ft_strlen(*istr);
	if (x > 0)
	{
		if (fg->minus)
			*istr = ft_free_strjoin(*istr, init_c_malloc(' ', x));
		else
			*istr = ft_free_strjoin(init_c_malloc(' ', x), *istr);
	}
}

void			add_zero(char **istr, int minus, t_flags *fg)
{
	int			nlen;
	int			x;

	nlen = ft_strlen(*istr);
	if (fg->precision > 0)
	{
		x = fg->precision - nlen;
		if (x >= 0)
			*istr = ft_free_strjoin(init_c_malloc('0', x), *istr);
	}
	else
	{
		x = fg->width - nlen;
		if (!fg->minus && fg->zero && x > 0 && fg->pf == 0)
			*istr = ft_free_strjoin(init_c_malloc('0', x + minus), *istr);
	}
}

static char		*int_to_istr(t_flags *flag, va_list ap)
{
	char		*istr;
	char		*mstr;
	int			mf;
	long long	para_int;

	mf = 0;
	para_int = va_arg(ap, int);
	if (para_int < 0)
	{
		mf = -1;
		para_int *= -1;
	}
	istr = ft_itoa(para_int);
	if (para_int == 0 && flag->precision == 0 && flag->dot == 1)
	{
		free(istr);
		istr = ft_strdup("");
	}
	add_zero(&istr, mf, flag);
	if (mf == -1)
	{
		mstr = ft_strdup("-");
		istr = ft_free_strjoin(mstr, istr);
	}
	return (istr);
}

int				ft_print_digit(t_flags *flag, va_list ap)
{
	int			slen;
	char		*istr;

	istr = int_to_istr(flag, ap);
	add_space(&istr, flag);
	ft_putstr(istr);
	slen = ft_strlen(istr);
	free(istr);
	return (slen);
}
