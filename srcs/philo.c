#include "../includes/philo.h"

static void	ft_ending(t_data *data, t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_detach(philo[i].philosopher_thread);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->mutex_food));
	pthread_mutex_destroy(&(data->mutex_print));
}

static int	ft_init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
		{
			printf("error: init forks!\n");
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&(data->mutex_food), NULL) != 0)
	{
		printf("error: init mutex!\n");
		return (1);
	}
	if (pthread_mutex_init(&(data->mutex_print), NULL) != 0)
	{
		printf("error: init mutex!\n");
		return (1);
	}
	return (0);
}

static void	ft_init_data(int argc, char **argv, t_data *data)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		data->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
}

static void	ft_parse_and_init(int argc, char **argv, t_data *data,
								 t_philosopher *philo)
{
	int	i;

	i = 0;
	ft_init_data(argc, argv, data);
	while (i < data->number_of_philosophers)
	{
		philo[i].index = i;
		if (i == data->number_of_philosophers - 1)
		{
			philo[i].right_fork = 0;
			philo[i].left_fork = i;
		}
		else
		{
			philo[i].right_fork = i + 1;
			philo[i].left_fork = i;
		}
		philo[i].number_of_times_ate = 0;
		philo[i].philosopher_dataset = data;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philosopher	philo[250];
	t_data			data;

	if (argc < 5 || argc > 6)
	{
		printf("error: incorrect data\n");
		return (1);
	}
	else
	{
		ft_parse_and_init(argc, argv, &data, philo);
		if ((ft_init_forks(&data) != 0)
			|| (ft_philosophers_threads(&data, philo) != 0))
			return (1);
		ft_waiter(&data, philo);
		ft_ending(&data, philo);
	}
	return (0);
}
