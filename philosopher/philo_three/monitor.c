/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:16:32 by ekim              #+#    #+#             */
/*   Updated: 2021/04/05 00:33:35 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void				*monitoring(void *param)
{
	t_ones			*ones;
	int				diff;

	ones = (t_ones *)param;
	while (1)
	{
		if (ones->eat_cnt == ones->philo->l_meals)
		{
			ones->full = 1;
			return (0);
		}
		diff = get_time() - ones->dining_time;
		if (diff >= ones->philo->t_die)
		{
			ones->philo->dead = 1;
			return (0);
		}
		if (ones->philo->dead)
			return (0);
		usleep(1000);
	}
}
