/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:35:55 by ekim              #+#    #+#             */
/*   Updated: 2021/04/12 11:36:38 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int					kill_process(t_philo *philo)
{
	int				i;

	i = 0;
	while (i < philo->total)
	{
		kill(philo->ones[i].pid, SIGKILL);
		i++;
	}
	return (1);
}

void				*monitoring(void *param)
{
	t_ones			*ones;
	int				diff;

	ones = (t_ones *)param;
	while (1)
	{
		if (ones->eat_cnt == ones->philo->l_meals)
			return (0);
		diff = get_time() - ones->dining_time;
		if (diff > ones->philo->t_die)
		{
			ones->philo->dead = ones->position;
			sem_post(ones->philo->death);
			return (0);
		}
		usleep(1000);
	}
}

void				*death_monitor(void *param)
{
	t_philo			*philo;

	philo = (t_philo *)param;
	sem_wait(philo->death);
	kill_process(philo);
	printf("One of Philosophers is dead...\n");
	sem_post(philo->process);
	return (0);
}

void				*full_monitor(void *param)
{
	int				full;
	t_philo			*philo;

	philo = (t_philo *)param;
	full = 0;
	while (1)
	{
		sem_wait(philo->exit_check);
		full++;
		if (full == philo->total)
		{
			kill_process(philo);
			printf("All Philosophers have had enough meals\n");
			sem_post(philo->process);
			return (0);
		}
	}
	return (0);
}
