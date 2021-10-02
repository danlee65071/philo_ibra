#include "../includes/philo.h"

static long	calc_time(struct timeval time)
{
	struct timeval	current_time;
	long			time_in_ms;

	gettimeofday(&current_time, NULL);
	time_in_ms = (current_time.tv_sec - time.tv_sec) * 1000
		+ (current_time.tv_usec - time.tv_usec) / 1000;
	return (time_in_ms);
}

static void	philosopher_time_sleep(struct timeval start, int time_sleep)
{
	long	till_time;

	till_time = calc_time(start) + time_sleep;
	while (calc_time(start) < till_time)
		usleep(100);
}

static void	philosopher_eat(t_data *data, t_philosopher *philo)
{
	pthread_mutex_lock(&(data->forks[philo->left_fork]));
	pthread_mutex_lock(&(data->mutex_print));
	printf("%ld %d has taken a fork\n", calc_time(data->start),
		philo->index + 1);
	pthread_mutex_unlock(&(data->mutex_print));
	pthread_mutex_lock(&(data->forks[philo->right_fork]));
	pthread_mutex_lock(&(data->mutex_print));
	printf("%ld %d has taken a fork\n", calc_time(data->start),
		philo->index + 1);
	pthread_mutex_unlock(&(data->mutex_print));
	pthread_mutex_lock(&(data->mutex_food));
	gettimeofday(&(philo->last_time_eating), NULL);
	pthread_mutex_lock(&(data->mutex_print));
	printf("%ld %d is eating\n", calc_time(data->start),
		philo->index + 1);
	pthread_mutex_unlock(&(data->mutex_print));
	(philo->number_of_times_ate)++;
	if (data->everyone_is_full != 1)
		pthread_mutex_unlock(&(data->mutex_food));
	philosopher_time_sleep(data->start, data->time_to_eat);
	pthread_mutex_unlock(&(data->forks[philo->right_fork]));
	pthread_mutex_unlock(&(data->forks[philo->left_fork]));
}

static void	*philosopher_life(void *args)
{
	t_data			*data;
	t_philosopher	*philo;

	philo = (t_philosopher *)args;
	data = philo->philosopher_dataset;
	if (philo->index % 2 != 0)
		usleep(300);
	while (data->dead != 1)
	{
		usleep(100);
		philosopher_eat(data, philo);
		pthread_mutex_lock(&(data->mutex_print));
		printf("%ld %d is sleeping\n", calc_time(data->start),
			philo->index + 1);
		pthread_mutex_unlock(&(data->mutex_print));
		philosopher_time_sleep(data->start, data->time_to_sleep);
		pthread_mutex_lock(&(data->mutex_print));
		printf("%ld %d is thinking\n", calc_time(data->start),
			philo->index + 1);
		pthread_mutex_unlock(&(data->mutex_print));
	}
	return (NULL);
}

int	ft_philosophers_threads(t_data *data, t_philosopher *philo)
{
	int	i;

	i = -1;
	gettimeofday(&(data->start), NULL);
	while (++i < data->number_of_philosophers)
	{
		gettimeofday(&(philo[i].last_time_eating), NULL);
		if (pthread_create(&(philo[i].philosopher_thread), NULL,
				philosopher_life, (void *) &(philo[i])) != 0)
		{
			printf("Philo thread create error!\n");
			return (1);
		}
	}
	return (0);
}
