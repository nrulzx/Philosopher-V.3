/* ============================= START_PROCESS ============================= */

#include "../inc/philo.h"

int	start_process(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start_time = get_time();
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->meal_mutex);
		data->threads[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->threads[i].thread, NULL, thread_action,
				&data->threads[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_process, data) != 0)
		return (1);
	if (pthread_join(monitor, NULL) != 0)
		return (1);
	return (0);
}
