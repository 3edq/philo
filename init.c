#include "philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (ERROR);
	
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals_required = (argc == 6) ? ft_atoi(argv[5]) : -1;
	data->simulation_end = false;
	
	if (data->num_philos <= 0 || data->time_to_die <= 0 ||
		data->time_to_eat <= 0 || data->time_to_sleep <= 0 ||
		(argc == 6 && data->meals_required <= 0))
		return (ERROR);
	
	return (SUCCESS);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (ERROR);
	
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ERROR);
		i++;
	}
	
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->end_lock, NULL) != 0)
		return (ERROR);
	
	return (SUCCESS);
}

int	init_philos(t_philo **philos, t_data *data)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
		return (ERROR);
	
	i = 0;
	while (i < data->num_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].left_fork = i;
		(*philos)[i].right_fork = (i + 1) % data->num_philos;
		(*philos)[i].last_meal_time = 0;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].is_eating = false;
		(*philos)[i].data = data;
		if (pthread_mutex_init(&(*philos)[i].meal_lock, NULL) != 0)
			return (ERROR);
		i++;
	}
	
	return (SUCCESS);
} 