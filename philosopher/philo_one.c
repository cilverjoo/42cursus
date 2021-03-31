#include <pthread.h>
#include <unistd.h> //usleep
#include <stdio.h>
#include <stdlib.h>

typedef struct			s_ones
{
	int					position;
	int					is_eating;
	int					l_fork;
	int					r_fork;
	int					eat_cnt;
	uint64_t			start;
	uint64_t			limit;
	t_philo				*philo;
	pthread_mutex_t		mutex;
	pthread_mutex_t		state;
}						t_ones;

typedef struct			s_philo
{
	int					total;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					l_meals;
	t_ones				*ones;
	pthread_mutex_t		*forks;
	pthread_mutex_t		state_m;
}						t_philo;

int				ft_strlen(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int				ft_atoi(char *num)
{
	int			ret;
	int			len;
	int			i;
	int			minus;

	ret = 0;
	minus = 1;
	i = 0;
	if (*num == '-' || *num == '+')
	{
		if (*num == '-')
			minus = -1;
		i++;
	}
	len = ft_strlen(num);
	while (i < len)
	{
		ret = ret * 10 + num[i] - '0';
		i++;
	}
	return (ret * minus);
}


uint64_t	get_time(t_philo *philo)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int			init_forks(t_philo *philo)
{
	int		i;

	i = 0;
	if (!(philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo->total)))
		return (0);
	while (i < philo->total)
		pthread_mutex_init(&philo->forks[i++], NULL);
	return (1);
}

void		init_ones(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->total)
	{
		philo->ones[i].position = i;
		philo->ones[i].l_fork = i;
		philo->ones[i].r_fork = (i + 1) % 5;
		philo->ones[i].eat_cnt = 0;
		philo->ones[i].is_eating = 0;
		philo->ones[i].philo = philo;
		pthread_mutex_init(&philo->ones[i].mutex, NULL);
		i++;
	}
	return (1);
}

int			init_philo(char **av, int ac, t_philo *philo)
{
	philo->total = ft_atoi(av[1]);
	philo->t_die = ft_atoi(av[2]) * 1000;
	philo->t_eat = ft_atoi(av[3]) * 1000;
	philo->t_sleep = ft_atoi(av[4]) * 1000;
	philo->l_meals = 0;
	if (ac == 6)
		philo->l_meals = ft_atoi(av[5]);
	if (philo->total < 2 || philo->l_meals < 0)
		return (0);
	if (!(philo->ones = (t_ones *)malloc(sizeof(t_ones) * ac)))
		return (0);
	init_ones(philo);
	init_forks(philo);
}


int				main(int ac, char **av)
{
	t_philo		philo;
	pthread_t	p_t;

	if (ac != 5 || ac != 6)
		return (exit_program());
	init_philo(av, ac, &philo);


	return (0);
}