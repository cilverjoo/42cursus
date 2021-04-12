/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:13:26 by ekim              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/04/07 21:13:21 by ekim             ###   ########.fr       */
=======
/*   Updated: 2021/04/06 21:52:11 by ekim             ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int					dining_philosophers(t_ones *ones)
{
	pthread_t		monitor_th;

	if (ones->position % 2 == 0)
<<<<<<< HEAD
		timer(1, get_time());
=======
		usleep(50);
>>>>>>> main
	ones->dining_time = get_time();
	pthread_create(&monitor_th, NULL, monitoring, (void *)ones);
	pthread_detach(monitor_th);
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
	sem_post(ones->philo->exit_check);
	return (0);
}

void				wait_childprocess(t_philo *philo)
{
	pthread_t		th_death;
	pthread_t		th_full;

	pthread_create(&th_death, NULL, &death_monitor, (void *)philo);
	pthread_create(&th_full, NULL, &full_monitor, (void *)philo);
	pthread_detach(th_death);
	pthread_detach(th_full);
	sem_wait(philo->process);
<<<<<<< HEAD
=======
	kill_process(philo);
>>>>>>> main
	clear_all(philo);
}

void				init_starttime(t_philo *philo)
{
	int				i;
<<<<<<< HEAD

=======
	
>>>>>>> main
	i = 0;
	philo->start = get_time();
	while (i < philo->total)
		philo->ones[i++].start = philo->start;
}

int					execute_philosophers(t_philo *philo, int total)
{
	int				i;

	i = 0;
	init_starttime(philo);
	while (i < total)
	{
		philo->ones[i].pid = fork();
		if (philo->ones[i].pid == 0)
			break ;
		i++;
	}
	if (i != philo->total)
	{
		dining_philosophers(&philo->ones[i]);
		exit(0);
	}
	else
		wait_childprocess(philo);
	return (1);
}

int					main(int ac, char **av)
{
	t_philo			philo;

	if (ac < 5 || ac > 6 || !init_philo(av, ac, &philo))
	{
		printf("Argument Error\n");
		return (0);
	}
	execute_philosophers(&philo, philo.total);
	return (0);
}
