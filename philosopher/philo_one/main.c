/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:13:26 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/04 17:11:23 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void				*dining_philosophers(void *param)
{
	t_ones			*ones;
	pthread_t		monitor_th;

	ones = (t_ones *)param;
	if (ones->position % 2 == 0)
		timer(1, get_time());
	ones->dining_time = get_time();
	pthread_create(&monitor_th, NULL, monitoring, (void *)ones);
	while (ones->philo->dead == 0
		&& (ones->philo->l_meals == -1 || ones->eat_cnt < ones->philo->l_meals))
	{
		if (!pickup(ones))
			break ;
		if (!eat(ones))
			break ;
		if (!putdown(ones))
			break ;
	}
	pthread_detach(monitor_th);
	return (0);
}

int					execute_philosophers(t_philo *philo, int total)
{
	pthread_t		thread[total];
	int				i;

	i = 0;
	while (i < total && philo->dead == 0)
	{
		pthread_create(&thread[i], NULL, dining_philosophers,
			(void *)&philo->ones[i]);
		i++;
	}
	i = 0;
	while (i < total)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	return (0);
}

int					check_dinning_status(t_philo *philo)
{
	int				i;

	i = 0;
	pthread_mutex_lock(&philo->output);
	if (philo->dead != 0)
		printf("%5.5llu Philosopher %d is dead\n",
			get_time() - philo->start, philo->dead);
	else
		printf("All Philosophers have had enough meals\n");
	pthread_mutex_unlock(&philo->output);
	pthread_mutex_destroy(&philo->output);
	return (1);
}

int					main(int ac, char **av)
{
	t_philo			philo;

	if (ac < 5 || ac > 6)
	{
		printf("Argument Error\n");
		exit(0);
	}
	init_philo(av, ac, &philo);
	execute_philosophers(&philo, philo.total);
	check_dinning_status(&philo);
	clear_mutex(&philo);
	return (0);
}
