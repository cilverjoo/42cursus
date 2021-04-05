/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:13:52 by ekim              #+#    #+#             */
/*   Updated: 2021/04/05 16:25:42 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int					pickup(t_ones *ones)
{
	sem_wait(ones->philo->forks);
	if (ones->philo->dead)
		return (0);
	sem_wait(ones->philo->output);
	printf("%5.5llu %d Philosopher has taken a left fork\n",
		get_time() - ones->start, ones->position);
	sem_post(ones->philo->output);
	sem_wait(ones->philo->forks);
	if (ones->philo->dead)
		return (0);
	sem_wait(ones->philo->output);
	printf("%5.5llu %d Philosopher has taken a right fork\n",
		get_time() - ones->start, ones->position);
	sem_post(ones->philo->output);
	return (1);
}

int					eat(t_ones *ones)
{
	if (ones->philo->dead)
		return (0);
	ones->dining_time = get_time();
	sem_wait(ones->philo->output);
	printf("%5.5llu %d Philosopher is eating...\n",
		get_time() - ones->start, ones->position);
	ones->eat_cnt++;
	sem_post(ones->philo->output);
	timer(ones->philo->t_eat, get_time());
	return (1);
}

int					putdown(t_ones *ones)
{
	sem_post(ones->philo->forks);
	sem_post(ones->philo->forks);
	if (ones->philo->dead)
		return (0);
	sem_wait(ones->philo->output);
	printf("%5.5llu %d Philosopher is sleeping...\n",
		get_time() - ones->start, ones->position);
	sem_post(ones->philo->output);
	timer(ones->philo->t_sleep, get_time());
	if (ones->philo->dead)
		return (0);
	sem_wait(ones->philo->output);
	printf("%5.5llu %d Philosopher is thinking...\n",
		get_time() - ones->start, ones->position);
	sem_post(ones->philo->output);
	return (1);
}
