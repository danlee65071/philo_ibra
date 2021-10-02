#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				dead;
	int				everyone_is_full;
	struct timeval	start;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	mutex_food;
	pthread_mutex_t	mutex_print;
}	t_data;

typedef struct s_philosopher
{
	int				index;
	int				right_fork;
	int				left_fork;
	struct timeval	last_time_eating;
	int				number_of_times_ate;
	pthread_t		philosopher_thread;
	t_data			*philosopher_dataset;
}	t_philosopher;

int		ft_atoi(const char *str);
int		ft_philosophers_threads(t_data *data, t_philosopher *philo);
void	ft_waiter(t_data *data, t_philosopher *philo);

#endif
