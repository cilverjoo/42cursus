/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:13:26 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/05 01:36:52 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void				*dining_philosophers(t_ones *ones)
{
	pthread_t		monitor_th;

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

int		kill_process(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->total)
	{
		kill(philo->ones[i].pid, SIGKILL);
		i++;
	}
	sem_post(philo->state);
	sem_wait(philo->state);
	printf("All process killed\n");
	sem_post(philo->state);
	return (1);
}

void	wait_childprocess(t_philo *philo)
{
	int		i;
	int		status;
	int		eat;

	eat = 0;
	while (1)
	{
		i = -1;
		while (++i < philo->total)
		{
			status = -1;
			waitpid(philo->ones[i].pid, &status, WNOHANG);
			if (status == 256 || status == 0)
			{
				if (status == 0)
					if (++eat != philo->total)
						continue ;
				break ;
			}
		}
		if (status == 256 || eat == philo->total)
			if (kill_process(philo))
				break ;
	}
}

int					execute_philosophers(t_philo *philo, int total)
{
	int				i;
	int				status;

	i = 0;
	status = 0;
	while (i < total && philo->dead == 0)
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
	// if (i != philo->total)
	// {
	// 	dining_philosophers(&philo->ones[i]);
	// 	exit(1);
	// }
	// else
	// 	wait_childprocess(philo);
	return (1);
}

int					check_dinning_status(t_philo *philo)
{
	int				i;

	i = 0;
	if (philo->dead != 0)
		printf("%5.5llu Philosopher %d is dead\n",
			get_time() - philo->start, philo->dead);
	else
		printf("%5.5llu All Philosophers have had enough meals\n", get_time() - philo->start);
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
	// clear_all(&philo);
	check_dinning_status(&philo);
	return (0);
}
