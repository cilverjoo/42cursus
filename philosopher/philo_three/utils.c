/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:25:09 by ekim              #+#    #+#             */
/*   Updated: 2021/04/12 10:27:42 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int					ft_strlen(char *str)
{
	int				i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int					ft_atoi(char *num)
{
	int				ret;
	int				len;
	int				i;

	ret = 0;
	i = 0;
	if (*num == '-' || *num == '+')
	{
		if (*num == '-')
			return (-1);
		i++;
	}
	len = ft_strlen(num);
	while (i < len)
	{
		if (num[i] < '0' || num[i] > '9')
			return (-1);
		ret = ret * 10 + num[i] - '0';
		i++;
	}
	return (ret);
}

uint64_t			get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int					timer(int wait, uint64_t start)
{
	int				time_diff;

	while (1)
	{
		time_diff = get_time() - start;
		if ((int)time_diff >= wait)
			return (1);
		usleep(100);
	}
	return (0);
}

int					clear_all(t_philo *philo)
{
	sem_unlink("/forks");
	sem_unlink("/state");
	sem_unlink("/exit_check");
	sem_unlink("/death");
	sem_unlink("/process");
	free(philo->ones);
	return (1);
}
