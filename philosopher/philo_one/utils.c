/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:25:09 by ekim              #+#    #+#             */
/*   Updated: 2021/04/01 16:24:03 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int				ft_strlen(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int				ft_atoi(char *num)
{
	int			ret;
	int			len;
	int			i;
	int			minus;

	ret = 0;
	minus = 1;
	i = 0;
	if (*num == '-' || *num == '+')
	{
		if (*num == '-')
			minus = -1;
		i++;
	}
	len = ft_strlen(num);
	while (i < len)
	{
		ret = ret * 10 + num[i] - '0';
		i++;
	}
	return (ret * minus);
}

uint64_t	get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
