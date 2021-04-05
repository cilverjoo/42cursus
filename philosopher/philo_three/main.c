/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:13:26 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/05 16:24:26 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int					dining_philosophers(t_ones *ones)
{
	pthread_t		monitor_th;

	ones->start = get_time();
	ones->dining_time = ones->start;
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
	pthread_join(monitor_th, NULL);
	sem_post(ones->philo->exit_check);
	return (0);
}

void				wait_childprocess(t_philo *philo)
{
	int				i;
	pthread_t		th_death;
	pthread_t		th_full;

	i = 0;
	pthread_create(&th_death, NULL, &death_monitor, (void *)philo);
	pthread_create(&th_full, NULL, &full_monitor, (void *)philo);
	pthread_detach(th_death);
	pthread_detach(th_full);
	sem_wait(philo->process);
	clear_all(philo);
	exit(0);
}

int					execute_philosophers(t_philo *philo, int total)
{
	int				i;
	pid_t			process[total];

	i = 0;
	while (i < total && philo->dead == 0)
	{
		process[i] = fork();
		if (process[i] == 0)
			break ;
		philo->ones[i].pid = process[i];
		i++;
		if (i == philo->total)
			sem_post(philo->process);
	}
	if (i != philo->total)
	{
		dining_philosophers(&philo->ones[i]);
		exit(0);
	}
	else
	{
		sem_wait(philo->process);
		wait_childprocess(philo);
	}
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
	return (0);
}
