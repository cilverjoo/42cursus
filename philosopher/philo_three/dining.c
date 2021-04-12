/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 14:13:52 by ekim              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/04/07 21:00:07 by ekim             ###   ########.fr       */
=======
/*   Updated: 2021/04/06 21:53:26 by ekim             ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int				pickup(t_ones *ones)
{
	sem_wait(ones->philo->forks);
	if (ones->philo->dead)
		return (0);
	sem_wait(ones->philo->state);
	printf("%5.5llu %d Philosopher has taken a left fork\n",
		get_time() - ones->start, ones->position);
	sem_post(ones->philo->state);
	sem_wait(ones->philo->forks);
	if (ones->philo->dead)
		return (0);
	sem_wait(ones->philo->state);
	printf("%5.5llu %d Philosopher has taken a right fork\n",
		get_time() - ones->start, ones->position);
	sem_post(ones->philo->state);
	return (1);
}

int				eat(t_ones *ones)
{
	if (ones->philo->dead)
<<<<<<< HEAD
		return (0);
	ones->dining_time = get_time();
=======
	{
		sem_post(ones->philo->forks);
		sem_post(ones->philo->forks);
		return (0);
	}
	ones->dining_time = get_time();	
>>>>>>> main
	sem_wait(ones->philo->state);
	printf("%5.5llu %d Philosopher is eating...\n",
		get_time() - ones->start, ones->position);
	sem_post(ones->philo->state);
	timer(ones->philo->t_eat, get_time());
	ones->eat_cnt++;
	return (1);
}

int				putdown(t_ones *ones)
{
	sem_post(ones->philo->forks);
	sem_post(ones->philo->forks);
	if (ones->philo->dead || ones->eat_cnt == ones->philo->l_meals)
		return (0);
	sem_wait(ones->philo->state);
	printf("%5.5llu %d Philosopher is sleeping...\n",
		get_time() - ones->start, ones->position);
	sem_post(ones->philo->state);
	timer(ones->philo->t_sleep, get_time());
	if (ones->philo->dead)
		return (0);
	sem_wait(ones->philo->state);
	printf("%5.5llu %d Philosopher is thinking...\n",
		get_time() - ones->start, ones->position);
	sem_post(ones->philo->state);
	return (1);
}
