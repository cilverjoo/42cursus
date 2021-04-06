/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:17:51 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/05 18:19:57 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

struct s_philo;

typedef struct			s_ones
{
	int					position;
	int					eat_cnt;
	uint64_t			start;
	uint64_t			dining_time;
	struct s_philo		*philo;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		state_msg;
	pthread_mutex_t		eat_monitor;
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
	t_ones				*ones;
	pthread_mutex_t		deadman;
	pthread_mutex_t		*forks;
	pthread_mutex_t		output;
}						t_philo;

int						init_philo(char **av, int ac, t_philo *philo);
int						init_ones(t_philo *philo, t_ones *ones);
int						init_forks(t_philo *philo);

int						pickup(t_ones *ones);
int						eat(t_ones *ones);
int						putdown(t_ones *ones);

void					*monitoring(void *param);
void					*die_monitor(void *param);

int						ft_strlen(char *str);
int						ft_atoi(char *num);
uint64_t				get_time(void);
int						timer(int wait, uint64_t start);
int						clear_mutex(t_philo *philo);

#endif
