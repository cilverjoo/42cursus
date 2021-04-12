/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:16:32 by ekim              #+#    #+#             */
/*   Updated: 2021/04/07 20:17:23 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void				*monitoring(void *param)
{
	t_ones			*ones;
	int				diff;

	ones = (t_ones *)param;
	while (1)
	{
		if (ones->eat_cnt == ones->philo->l_meals || ones->philo->dead)
			return (0);
		diff = get_time() - ones->dining_time;
		if (diff > ones->philo->t_die)
		{
			sem_wait(ones->philo->output);
			ones->philo->dead = 1;
			sem_post(ones->philo->output);
			return (0);
		}
		usleep(1000);
	}
}
