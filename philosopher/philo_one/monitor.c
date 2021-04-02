/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:16:32 by ekim              #+#    #+#             */
/*   Updated: 2021/04/02 18:30:01 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void				*die_monitor(void *param)
{
	t_ones			*ones;
	int				diff;
	int				die;
			
	ones = (t_ones*)param;
	die = ones->philo->t_die;
	while (ones->is_eating)
	{
		diff = get_time() - ones->dining_time;
		if (diff >= die)
		{
			ones->philo->dead = 1;
			return (0);
		}
	}
	return (0);
}

void				*monitoring(void *param)
{
	t_ones			*ones;
	
	ones = (t_ones *)param;
	while (1)
	{
		if (ones->philo->l_meals == -1)
		{
			if (ones->philo->dead == 1)
				return (0);
			continue ;
		}
		else if (ones->eat_cnt >= ones->philo->l_meals)
		{
			ones->full = 1;
			return (0);
		}
	}
}
