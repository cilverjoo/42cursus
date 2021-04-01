/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:25:31 by ekim              #+#    #+#             */
/*   Updated: 2021/04/01 21:08:37 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					timer(int wait, uint64_t start)
{
	int				time_diff;
	
	while (1)
	{
		time_diff = get_time() - start;
		if ((int)time_diff >= wait)
			return (1);
	}
	return (0);
}

void				*die_monitor(void *param)
{
	t_ones			*ones;
	int				diff;
	int				die;
			
	ones = (t_ones*)param;
	die = ones->philo->t_die;
	while (1)
	{
		diff = get_time() - ones->dining_time;
		if (diff >= die)
		{
			ones->dead = 1;
			return (0);
		}
		usleep(1000);
	}
	return (0);
}

int					pickup(t_ones *ones)
{
	pthread_mutex_lock(ones->l_fork);
	
	pthread_mutex_lock(ones->state_m);
	printf("%5.5lu %d Philosopher has taken a left fork\n", get_time() - ones->start, ones->position);
	pthread_mutex_unlock(ones->state_m);
	
	pthread_mutex_lock(ones->r_fork);
	
	pthread_mutex_lock(ones->state_m);
	printf("%5.5lu %d Philosopher has taken a right fork\n", get_time() - ones->start, ones->position);
	pthread_mutex_unlock(ones->state_m);
	return (0);
}

int					eat(t_ones *ones)
{
	pthread_t		monitor;
	
	ones->dining_time = get_time();
	
	pthread_create(&monitor, NULL, &die_monitor, (void *)ones);

	pthread_mutex_lock(ones->state_m);
	printf("%5.5lu %d Philosopher is eating...\n", get_time() - ones->start, ones->position);
	pthread_mutex_unlock(ones->state_m);
	
	timer(ones->philo->t_eat, get_time());

	pthread_detach(monitor);
	
	if (ones->eat_cnt != -1)
		ones->eat_cnt++;
	return (0);
}

int					putdown(t_ones *ones)
{	
	pthread_mutex_unlock(ones->l_fork);
	pthread_mutex_unlock(ones->r_fork);
	
	pthread_mutex_lock(ones->state_m);
	printf("%5.5lu %d Philosopher is sleeping...\n", get_time() - ones->start, ones->position);
	pthread_mutex_unlock(ones->state_m);
	
	timer(ones->philo->t_sleep, get_time());
	
	pthread_mutex_lock(ones->state_m);
	printf("%5.5lu %d Philosopher is thinking...\n", get_time() - ones->start, ones->position);
	pthread_mutex_unlock(ones->state_m);
	
	return (0);
}

void				*monitoring(void *param)
{
	t_ones			*ones;
	
	ones = (t_ones *)param;
	while (!ones->dead)
	{
		if (ones->philo->l_meals == -1)
			continue ;
		else if (ones->eat_cnt >= ones->philo->l_meals)
		{
			ones->philo->eat_all += 1;
			ones->dead = 1;
			return (0);
		}
	}
	ones->philo->dead = -1;
	pthread_mutex_lock(ones->state_m);
	printf("Philosopher %d is dead\n", ones->position + 1);
	pthread_mutex_unlock(ones->state_m);
	exit(0);
}

void 				*dining_philosophers(void *param)
{
	t_ones			*ones;
	pthread_t		monitor_th;
	
	ones = (t_ones *)param;
	pthread_create(&monitor_th, NULL, monitoring, (void *)ones);
	pthread_detach(monitor_th);
	while (ones->dead == 0)
	{
		pickup(ones);
		eat(ones);
		putdown(ones);
	}
	return (0);
}

int					execute_philosophers(t_philo *philo, int total)
{
	pthread_t		thread[total];
	int				i;

	i = 0;
	
	while (i < philo->total && philo->dead == 0)
	{
		pthread_create(&thread[i], NULL, dining_philosophers, (void *)&philo->ones[i]);
		i++;
	}
	i = 0;
	while (i < philo->total)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	return (0);
}

int 			check_dinning_status(t_philo *philo)
{
	if (philo->eat_all == philo->total)
	{
		pthread_mutex_lock(&philo->output);
		printf("All Philosophers have had enough meals\n");
		pthread_mutex_unlock(&philo->output);
	}
	else
		printf("Opps..");
	return (1);
}

int				main(int ac, char **av)
{
	t_philo		philo;

	if (ac < 5 || ac > 6)
	{
		printf("Argument Error\n");
		exit(0);
	}
	init_philo(av, ac, &philo);
	execute_philosophers(&philo, philo.total);
	check_dinning_status(&philo);

	return (0);
}
