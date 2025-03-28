#include "philo.h"

int	start_simulation(t_philo *philos, t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start_time = get_time_in_ms();
	
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher_routine, &philos[i]) != 0)
			return (ERROR);
		i++;
	}
	
	if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
		return (ERROR);
	
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (ERROR);
		i++;
	}
	
	if (pthread_join(monitor, NULL) != 0)
		return (ERROR);
	
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (init_data(&data, argc, argv) != SUCCESS)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	
	if (init_mutexes(&data) != SUCCESS)
	{
		printf("Error: Failed to initialize mutexes\n");
		return (1);
	}
	
	if (init_philos(&philos, &data) != SUCCESS)
	{
		printf("Error: Failed to initialize philosophers\n");
		free(data.forks);
		return (1);
	}
	
	if (start_simulation(philos, &data) != SUCCESS)
	{
		printf("Error: Failed to start simulation\n");
		cleanup(philos, &data);
		return (1);
	}
	
	cleanup(philos, &data);
	return (0);
}
