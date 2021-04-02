/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:13:52 by ekim              #+#    #+#             */
/*   Updated: 2021/04/02 18:17:02 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					pickup(t_ones *ones)
{
	pthread_mutex_lock(ones->l_fork);
	
	pthread_mutex_lock(ones->state_m);
	printf("%5.5llu %d Philosopher has taken a left fork\n", get_time() - ones->start, ones->position);
	pthread_mutex_unlock(ones->state_m);
	
	pthread_mutex_lock(ones->r_fork);
	
	pthread_mutex_lock(ones->state_m);
	printf("%5.5llu %d Philosopher has taken a right fork\n", get_time() - ones->start, ones->position);
	pthread_mutex_unlock(ones->state_m);
	return (0);
}

int					eat(t_ones *ones)
{
	pthread_t		monitor;
	pthread_mutex_t	mutex;
	
	pthread_mutex_lock(ones->state_m);
	printf("%5.5llu %d Philosopher is eating...\n", get_time() - ones->start, ones->position);
	pthread_mutex_unlock(ones->state_m);
	
	ones->is_eating = 1;
	ones->dining_time = get_time();
	pthread_create(&monitor, NULL, &die_monitor, (void *)ones);
	
	timer(ones->philo->t_eat, get_time());

	ones->is_eating = 0;
	pthread_detach(monitor);
	
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	ones->eat_cnt++;
	pthread_mutex_unlock(&mutex);
	return (0);
}

int					putdown(t_ones *ones)
{	
	pthread_mutex_unlock(ones->l_fork);
	pthread_mutex_unlock(ones->r_fork);
	
	pthread_mutex_lock(ones->state_m);
	printf("%5.5llu %d Philosopher is sleeping...\n", get_time() - ones->start, ones->position);
	pthread_mutex_unlock(ones->state_m);
	
	timer(ones->philo->t_sleep, get_time());
	
	pthread_mutex_lock(ones->state_m);
	printf("%5.5llu %d Philosopher is thinking...\n", get_time() - ones->start, ones->position);
	pthread_mutex_unlock(ones->state_m);
	
	return (0);
}
