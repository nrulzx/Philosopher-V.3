/* ========================== MONITOR_PROCESS ========================== */

#include "../inc/philo.h"

static int	check_died(t_thread *thread, int time_to_die)
{
	long	current_time;
	long	time_since_last_meal;

	pthread_mutex_lock(&thread->data->meal_mutex);
	current_time = get_time();
	time_since_last_meal = current_time - thread->last_meal;
	pthread_mutex_unlock(&thread->data->meal_mutex);
	return (time_since_last_meal > time_to_die);
}

int	check_philosopher_death(t_data *data, int i)
{
	if (check_died(&data->threads[i], data->time_to_die))
	{
		pthread_mutex_lock(&data->death_mutex);
		data->someone_died = true;
		pthread_mutex_unlock(&data->death_mutex);
		print_state(data, data->threads[i].id, "died");
		return (1);
	}
	return (0);
}

static int	check_all_ate(t_data *data)
{
	int	i;
	int	finished;

	if (data->must_eat < 0)
		return (0);
	i = 0;
	finished = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->threads[i].meals_count >= data->must_eat)
			finished++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (finished == data->philo_num);
}

int	check_meal_completion(t_data *data)
{
	if (check_all_ate(data))
	{
		pthread_mutex_lock(&data->death_mutex);
		data->all_ate = true;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_process(void *arg)
{
	t_data	*data;
	int		i;
	int		should_exit;

	data = (t_data *)arg;
	should_exit = 0;
	while (!should_exit)
	{
		i = 0;
		while (i < data->philo_num)
		{
			if (check_philosopher_death(data, i))
			{
				should_exit = 1;
				break ;
			}
			i++;
		}
		if (!should_exit && check_meal_completion(data))
			should_exit = 1;
		usleep(500);
	}
	return (NULL);
}
