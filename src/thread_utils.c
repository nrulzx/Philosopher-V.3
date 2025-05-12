#include "../inc/philo.h"

int	handle_single_philo(t_data *data, int right_fork)
{
	ft_sleep(data->time_to_die + 10);
	pthread_mutex_unlock(&data->forks[right_fork].mutex);
	return (1);
}

void	update_meal_time(t_thread *thread)
{
	pthread_mutex_lock(&thread->data->meal_mutex);
	thread->last_meal = get_time();
	thread->meals_count++;
	pthread_mutex_unlock(&thread->data->meal_mutex);
}

void	release_forks(t_data *data, int right_fork, int left_fork)
{
	pthread_mutex_unlock(&data->forks[right_fork].mutex);
	pthread_mutex_unlock(&data->forks[left_fork].mutex);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->threads[i].thread, NULL);
		i++;
	}
}

int	is_finish(t_thread *thread)
{
	t_data	*data;
	int		result;

	data = thread->data;
	result = 0;
	pthread_mutex_lock(&data->death_mutex);
	if (data->someone_died || data->all_ate)
		result = 1;
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}
