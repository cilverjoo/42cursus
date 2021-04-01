#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <unistd.h> //usleep
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

struct 					s_philo;

typedef struct			s_ones
{
	int					position;
	int					eat_cnt;
	int					dead;
	uint64_t			start;
	uint64_t			dining_time;
	struct s_philo		*philo;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*state_m;
}						t_ones;

typedef struct			s_philo
{
	int					total;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					l_meals;
	int					eat_all;
	int					dead;
	uint64_t			start;
	t_ones				*ones;
	pthread_mutex_t		*forks;
	pthread_mutex_t		output;
}						t_philo;


//init
int						init_philo(char **av, int ac, t_philo *philo);
int						init_ones(t_philo *philo, t_ones *ones);
int						init_forks(t_philo *philo);

//utils
int						ft_strlen(char *str);
int						ft_atoi(char *num);
uint64_t				get_time(void);



#endif
