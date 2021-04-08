/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:13:52 by ekim              #+#    #+#             */
/*   Updated: 2021/04/07 21:00:12 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					pickup(t_ones *ones)
{
	pthread_mutex_lock(ones->l_fork);
	if (ones->philo->dead)
		return (0);
	pthread_mutex_lock(&ones->philo->output);
	printf("%5.5llu %d Philosopher has taken a left fork\n",
		get_time() - ones->start, ones->position);
	pthread_mutex_unlock(&ones->philo->output);
	pthread_mutex_lock(ones->r_fork);
	if (ones->philo->dead)
		return (0);
	pthread_mutex_lock(&ones->philo->output);
	printf("%5.5llu %d Philosopher has taken a right fork\n",
		get_time() - ones->start, ones->position);
	pthread_mutex_unlock(&ones->philo->output);
	return (1);
}

int					eat(t_ones *ones)
{
	if (ones->philo->dead)
		return (0);
	ones->dining_time = get_time();
	pthread_mutex_lock(&ones->philo->output);
	printf("%5.5llu %d Philosopher is eating...\n",
		get_time() - ones->start, ones->position);
	pthread_mutex_unlock(&ones->philo->output);
	timer(ones->philo->t_eat, get_time());
	ones->eat_cnt++;
	return (1);
}

int					putdown(t_ones *ones)
{
	pthread_mutex_unlock(ones->l_fork);
	pthread_mutex_unlock(ones->r_fork);
	if (ones->philo->dead || ones->eat_cnt == ones->philo->l_meals)
		return (0);
	pthread_mutex_lock(&ones->philo->output);
	printf("%5.5llu %d Philosopher is sleeping...\n",
		get_time() - ones->start, ones->position);
	pthread_mutex_unlock(&ones->philo->output);
	timer(ones->philo->t_sleep, get_time());
	if (ones->philo->dead)
		return (0);
	pthread_mutex_lock(&ones->philo->output);
	printf("%5.5llu %d Philosopher is thinking...\n",
		get_time() - ones->start, ones->position);
	pthread_mutex_unlock(&ones->philo->output);
	return (1);
}
