/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:25:18 by ukim              #+#    #+#             */
/*   Updated: 2020/11/18 19:35:12 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			*change_base_to_string(unsigned long long num, char *base)
{
	int				len;
	char			*str;
	int				base_len;

	base_len = ft_strlen(base);
	len = ull_length(num, base_len);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	str[len] = '\0';
	while (num > 0)
	{
		str[len] = base[num % base_len];
		num /= base_len;
	}
	return (str);
}

int					ft_print_ux(t_flags *flag, va_list ap, char *base)
{
	int				i;
	unsigned int	num;
	char			*str;
	char			*tmp[2];
	char			c;

	num = va_arg(ap, unsigned int);
	str = change_base_to_string(num, base);
	if (num == 0 && flag->precision == 0)
		str[0] = '0';
	i = flag->precision - ft_strlen(str);
	if (i > 0)
	{
		tmp[0] = init_c_malloc('0', i);
		str = ft_free_strjoin(tmp[0], str);
	}
	i = flag->width - (int)ft_strlen(str);
	if (i > 0)
	{
		if (flag->minus)
		{
			tmp[0] = str;
			tmp[1] = init_c_malloc(' ', i);
		}
		else
		{
			c = flag->zero && flag->pf == 0 ? '0' : ' ';
			tmp[0] = init_c_malloc(c, i);
			tmp[1] = str;
		}
		str = ft_free_strjoin(tmp[0], tmp[1]);
	}
	ft_putstr(str);
	return (ft_strlen(str));
}