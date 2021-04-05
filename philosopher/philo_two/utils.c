/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:25:09 by ekim              #+#    #+#             */
/*   Updated: 2021/04/05 16:26:39 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

uint64_t		get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int				timer(int wait, uint64_t start)
{
	int			time_diff;

	while (1)
	{
		time_diff = get_time() - start;
		if ((int)time_diff >= wait)
			return (1);
	}
	return (0);
}

int				clear_all(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->output);
	free(philo->ones);
	return (1);
}
