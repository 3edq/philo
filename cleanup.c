#include "philo.h"

void	cleanup(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&philos[i].meal_lock);
		i++;
	}
	
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->end_lock);
	
	free(data->forks);
	free(philos);
} 