/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:17:10 by ekim              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/04/07 21:09:27 by ekim             ###   ########.fr       */
=======
/*   Updated: 2021/04/06 21:53:24 by ekim             ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <string.h>

struct s_philo;

typedef struct			s_ones
{
	int					position;
	int					eat_cnt;
	int					full;
	pid_t				pid;
	uint64_t			start;
	uint64_t			dining_time;
	struct s_philo		*philo;
}						t_ones;

typedef struct			s_philo
{
	int					total;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					l_meals;
	int					dead;
	uint64_t			start;
	sem_t				*philosopher;
	sem_t				*forks;
	sem_t				*state;
	sem_t				*exit_check;
	sem_t				*death;
	sem_t				*process;
	t_ones				*ones;
}						t_philo;

int						init_philo(char **av, int ac, t_philo *philo);
int						init_ones(t_philo *philo, t_ones *ones);
int						init_semaphore(t_philo *philo);

int						pickup(t_ones *ones);
int						eat(t_ones *ones);
int						putdown(t_ones *ones);

void					*monitoring(void *param);
void					*death_monitor(void *param);
void					*full_monitor(void *param);

int						ft_strlen(char *str);
int						ft_atoi(char *num);
uint64_t				get_time(void);
int						timer(int wait, uint64_t start);
int						clear_all(t_philo *philo);

int						kill_process(t_philo *philo);

#endif
