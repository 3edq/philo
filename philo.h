#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define SUCCESS 0
# define ERROR 1

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long			start_time;
	bool			simulation_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	end_lock;
} t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long			last_meal_time;
	int				meals_eaten;
	bool			is_eating;
	pthread_mutex_t	meal_lock;
	pthread_t		thread;
	t_data			*data;
} t_philo;

int		init_data(t_data *data, int argc, char **argv);
int		init_mutexes(t_data *data);
int		init_philos(t_philo **philos, t_data *data);

int		ft_atoi(const char *str);
long	get_time_in_ms(void);
void	print_status(t_philo *philo, char *status);
void	precise_sleep(int ms);
bool	simulation_should_end(t_data *data);

void	*philosopher_routine(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

void	*monitor_routine(void *arg);
bool	check_philo_death(t_philo *philo);
bool	check_all_eat(t_philo *philos, t_data *data);

#endif 