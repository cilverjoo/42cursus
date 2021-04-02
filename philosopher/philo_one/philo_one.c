/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:25:31 by ekim              #+#    #+#             */
/*   Updated: 2021/04/02 18:27:10 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void 				*dining_philosophers(void *param)
{
	t_ones			*ones;
	pthread_t		monitor_th;
	
	ones = (t_ones *)param;
	if (ones->position % 2 == 0)
		timer(10, get_time());
	pthread_create(&monitor_th, NULL, monitoring, (void *)ones);
	while (!ones->philo->dead && !ones->full)
	{
		pickup(ones);
		eat(ones);
		putdown(ones);
	}
	pthread_join(monitor_th, NULL);
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
		timer(50, get_time());
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
	int			i;
	
	i = 0;
	while (i < philo->total)
	{
		if (philo->ones[i].full != 1)
		{
			pthread_mutex_lock(philo->ones[i].state_m);
			printf("Philosopher %d is dead\n", philo->ones[i].position);
			pthread_mutex_unlock(philo->ones[i].state_m);
			exit(0);
		}
		i++;
	}
	printf("All Philosophers have had enough meals\n");
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
