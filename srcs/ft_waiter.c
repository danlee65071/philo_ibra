#include "philo.h"

static long	calc_time(struct timeval time)
{
	struct timeval	current_time;
	long			time_in_ms;

	gettimeofday(&current_time, NULL);
	time_in_ms = (current_time.tv_sec - time.tv_sec) * 1000
		+ (current_time.tv_usec - time.tv_usec) / 1000;
	return (time_in_ms);
}

static void	waiter_loop(t_data *data, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers && data->dead != 1)
	{
		pthread_mutex_lock(&(data->mutex_food));
		if (calc_time(philo[i].last_time_eating) > data->time_to_die)
		{
			pthread_mutex_lock(&(data->mutex_print));
			printf("%ld %d died\n", calc_time(data->start), i + 1);
			pthread_mutex_unlock(&(data->mutex_print));
			data->dead = 1;
		}
		pthread_mutex_unlock(&(data->mutex_food));
	}
}

void	ft_waiter(t_data *data, t_philosopher *philo)
{
	int	i;

	while (data->everyone_is_full != 1)
	{
		waiter_loop(data, philo);
		if (data->dead == 1)
			break ;
		i = 0;
		while (data->number_of_times_each_philosopher_must_eat != -1
			&& i < data->number_of_philosophers
			&& philo[i].number_of_times_ate
			>= data->number_of_times_each_philosopher_must_eat)
			i++;
		if (i == data->number_of_philosophers)
		{
			data->everyone_is_full = 1;
			return ;
		}
	}
}
