/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:26:54 by ekim              #+#    #+#             */
/*   Updated: 2021/04/05 00:47:59 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int					init_semaphore(t_philo *philo)
{
	int				i;
	char			*str;

	i = 1;
	sem_unlink("/forks");
	philo->forks = sem_open("/forks", O_CREAT, 0666, philo->total);
	sem_unlink("/output");
	philo->output = sem_open("/output", O_CREAT, 0666, 1);
	return (0);
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
		ones[i].start = philo->start;
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
	philo->start = get_time();
	init_ones(philo, philo->ones);
	return (1);
}
