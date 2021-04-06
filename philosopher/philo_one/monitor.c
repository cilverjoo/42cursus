/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:16:32 by ekim              #+#    #+#             */
/*   Updated: 2021/04/04 01:17:44 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void				*monitoring(void *param)
{
	t_ones			*ones;
	int				diff;

	ones = (t_ones *)param;
	while (1)
	{
		if (ones->eat_cnt == ones->philo->l_meals)
			return (0);
		diff = get_time() - ones->dining_time;
		if (diff >= ones->philo->t_die)
		{
			pthread_mutex_lock(&ones->philo->deadman);
			ones->philo->dead = ones->position;
			pthread_mutex_unlock(&ones->philo->deadman);
			return (0);
		}
		if (ones->philo->dead)
			return (0);
		usleep(1000);
	}
}
