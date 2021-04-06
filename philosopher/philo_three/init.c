/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:26:54 by ekim              #+#    #+#             */
/*   Updated: 2021/04/06 21:53:44 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int					init_semaphore(t_philo *philo)
{
	sem_unlink("/forks");
	philo->forks = sem_open("/forks", O_CREAT, 0666, philo->total);
	sem_unlink("/state");
	philo->state = sem_open("/state", O_CREAT, 0666, 1);
	sem_unlink("/exit_check");
	philo->exit_check = sem_open("/exit_check", O_CREAT, 0666, 0);
	sem_unlink("/death");
	philo->death = sem_open("/death", O_CREAT, 0666, 0);
	sem_unlink("/process");
	philo->process = sem_open("/process", O_CREAT, 0666, 0);
	return (1);
}

int					init_ones(t_philo *philo, t_ones *ones)
{
	int				i;

	i = 0;
	while (i < philo->total)
	{
		ones[i].position = i + 1;
		ones[i].eat_cnt = 0;
		ones[i].philo = philo;
		ones[i].dining_time = 0;
		i++;
	}
	return (1);
}

int					init_philo(char **av, int ac, t_philo *philo)
{
	philo->total = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	philo->t_sleep = ft_atoi(av[4]);
	philo->l_meals = -1;
	philo->dead = 0;
	if (ac == 6)
		philo->l_meals = ft_atoi(av[5]);
	if (philo->total < 2 || (philo->l_meals != -1 && philo->l_meals < 0))
		return (0);
	if (!(philo->ones = (t_ones *)malloc(sizeof(t_ones) * philo->total)))
		return (0);
	init_semaphore(philo);
	init_ones(philo, philo->ones);
	return (1);
}
