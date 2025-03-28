#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, "has taken a fork");
	
	if (philo->data->num_philos == 1)
	{
		precise_sleep(philo->data->time_to_die);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return ;
	}
	
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, "has taken a fork");
	
	pthread_mutex_lock(&philo->meal_lock);
	philo->is_eating = true;
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	
	print_status(philo, "is eating");
	precise_sleep(philo->data->time_to_eat);
	
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->meal_lock);
	
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = get_time_in_ms();
	
	// 奇数番号の哲学者は少し遅れて開始して、デッドロックを防ぐ
	if (philo->id % 2 == 0)
		precise_sleep(philo->data->time_to_eat / 2);
	
	while (!simulation_should_end(philo->data))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	
	return (NULL);
}
 