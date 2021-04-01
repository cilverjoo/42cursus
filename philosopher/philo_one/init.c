/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:26:54 by ekim              #+#    #+#             */
/*   Updated: 2021/04/01 20:33:45 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int					init_forks(t_philo *philo)
{
	int				i;

	i = 0;
	if (!(philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo->total)))
		return (0);
	while (i < philo->total)
		pthread_mutex_init(&philo->forks[i++], NULL);
	return (1);
}

int					init_ones(t_philo *philo, t_ones *ones)
{
	int				i;
	pthread_mutex_t mutex[philo->total];

	i = 0;
	while (i < philo->total)
	{
		ones[i].position = i + 1;
		if (philo->total != 2)
		{
			ones[i].l_fork = i > 0 ? &philo->forks[i - 1] : &philo->forks[philo->total - 1];
			ones[i].r_fork = i < philo->total - 1 ? &philo->forks[i + 1] : &philo->forks[0];
		}
		else
		{
			ones[i].l_fork = &philo->forks[0];
			ones[i].r_fork = &philo->forks[1];
		}
		ones[i].eat_cnt = 0;
		ones[i].philo = philo;
		ones[i].dead = 0;
		ones[i].start = philo->start;
		ones[i].dining_time = 0;
		pthread_mutex_init(&mutex[i], NULL);
		philo->ones[i].state_m = &mutex[i];
		i++;
	}
	return (1);
}

int			init_philo(char **av, int ac, t_philo *philo)
{	
	philo->total = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]);
	philo->t_eat = ft_atoi(av[3]);
	philo->t_sleep = ft_atoi(av[4]);
	philo->l_meals = -1;
	philo->dead = 0;
	philo->eat_all = 0;
	philo->start = get_time();
	if (ac == 6)
		philo->l_meals = ft_atoi(av[5]);
	if (philo->total < 2 || (philo->l_meals != -1 && philo->l_meals < 0))
		return (0);
	init_forks(philo);
	if (!(philo->ones = (t_ones *)malloc(sizeof(t_ones) * philo->total)))
		return (0);
	init_ones(philo, philo->ones);
	return (0);
}
