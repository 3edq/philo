#include "philo.h"

bool	check_philo_death(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;
	bool	is_eating;

	pthread_mutex_lock(&philo->meal_lock);
	current_time = get_time_in_ms();
	time_since_last_meal = current_time - philo->last_meal_time;
	is_eating = philo->is_eating;
	pthread_mutex_unlock(&philo->meal_lock);
	if (!is_eating && time_since_last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d died\n", current_time - philo->data->start_time,
			philo->id);
		pthread_mutex_lock(&philo->data->end_lock);
		philo->data->simulation_end = true;
		pthread_mutex_unlock(&philo->data->end_lock);
		pthread_mutex_unlock(&philo->data->print_lock);
		return (true);
	}
	return (false);
}

bool	check_all_eat(t_philo *philos, t_data *data)
{
	int	i;
	int	count;

	if (data->meals_required == -1)
		return (false);
	count = 0;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		if (philos[i].meals_eaten >= data->meals_required)
			count++;
		pthread_mutex_unlock(&philos[i].meal_lock);
		i++;
	}
	if (count == data->num_philos)
	{
		pthread_mutex_lock(&data->end_lock);
		data->simulation_end = true;
		pthread_mutex_unlock(&data->end_lock);
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	t_data	*data;
	int		i;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (!simulation_should_end(data))
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_philo_death(&philos[i]))
				return (NULL);
			i++;
		}
		if (check_all_eat(philos, data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
