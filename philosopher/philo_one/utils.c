/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:25:09 by ekim              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/04/07 20:53:07 by ekim             ###   ########.fr       */
=======
/*   Updated: 2021/04/05 18:20:10 by ekim             ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

int					clear_mutex(t_philo *philo)
{
	int				i;

	i = 0;
	while (i < philo->total)
	{
		pthread_mutex_destroy(&philo->forks[i]);
<<<<<<< HEAD
=======
		pthread_mutex_destroy(&philo->ones[i].state_msg);
		pthread_mutex_destroy(&philo->ones[i].eat_monitor);
>>>>>>> main
		i++;
	}
	pthread_mutex_destroy(&philo->deadman);
	pthread_mutex_destroy(&philo->output);
	free(philo->ones);
	free(philo->forks);
	return (1);
}
