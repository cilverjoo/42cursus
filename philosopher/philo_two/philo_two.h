/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 01:17:51 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/04/05 16:26:16 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

struct s_philo;

typedef struct			s_ones
{
	int					position;
	int					eat_cnt;
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
	sem_t				*forks;
	sem_t				*output;
	sem_t				*state;
	t_ones				*ones;
}						t_philo;

int						init_philo(char **av, int ac, t_philo *philo);
int						init_ones(t_philo *philo, t_ones *ones);
int						init_semaphore(t_philo *philo);

int						pickup(t_ones *ones);
int						eat(t_ones *ones);
int						putdown(t_ones *ones);

void					*monitoring(void *param);
void					*die_monitor(void *param);

int						ft_strlen(char *str);
int						ft_atoi(char *num);
uint64_t				get_time(void);
int						timer(int wait, uint64_t start);
int						clear_all(t_philo *philo);

#endif
