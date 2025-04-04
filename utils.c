#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool	simulation_should_end(t_data *data)
{
	bool	end;

	pthread_mutex_lock(&data->end_lock);
	end = data->simulation_end;
	pthread_mutex_unlock(&data->end_lock);
	return (end);
}

void	print_status(t_philo *philo, char *status)
{
	long	current_time;

	if (simulation_should_end(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	current_time = get_time_in_ms() - philo->data->start_time;
	printf("%ld %d %s\n", current_time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	precise_sleep(int ms)
{
	long	start_time;
	long	current_time;

	start_time = get_time_in_ms();
	while (1)
	{
		current_time = get_time_in_ms();
		if (current_time - start_time >= ms)
			break ;
		usleep(500);
	}
}
