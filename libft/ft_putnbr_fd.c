/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 22:56:53 by ekim              #+#    #+#             */
/*   Updated: 2020/10/12 23:35:35 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	char			c;

	num = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = (unsigned int)(n * -1);
	}
	if (num > 9)
		ft_putnbr_fd(num / 10, fd);
	c = num % 10 + '0';
	ft_putchar_fd(c, fd);
}
