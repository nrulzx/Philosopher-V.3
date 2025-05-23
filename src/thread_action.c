/* ============================= THREAD_ACTION ============================= */

#include "../inc/philo.h"

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

static int	philo_eat(t_thread *thread)
{
	t_data	*data;
	int		right_fork;
	int		left_fork;

	data = thread->data;
	set_fork_order(thread, &right_fork, &left_fork);
	if (take_forks(thread, right_fork, left_fork))
		return (1);
	if (is_finish(thread))
	{
		release_forks(data, right_fork, left_fork);
		return (1);
	}
	print_state(data, thread->id, "is eating");
	thread->state = EATING;
	update_meal_time(thread);
	ft_sleep(data->time_to_eat);
	release_forks(data, right_fork, left_fork);
	return (0);
}

static int	philo_action(t_thread *thread, t_state state)
{
	t_data	*data;
	int		think_time;

	data = thread->data;
	if (state == SLEEPING)
	{
		print_state(data, thread->id, "is sleeping");
		thread->state = SLEEPING;
		ft_sleep(data->time_to_sleep);
	}
	else if (state == THINKING)
	{
		print_state(data, thread->id, "is thinking");
		thread->state = THINKING;
		think_time = 1;
		if (data->time_to_die > data->time_to_eat + data->time_to_sleep)
			think_time = (data->time_to_die - data->time_to_eat
					- data->time_to_sleep) / 2;
		usleep(think_time * 100);
	}
	if (is_finish(thread))
		return (1);
	return (0);
}

void	*thread_action(void *arg)
{
	t_thread	*thread;

	thread = (t_thread *)arg;
	if (thread->id % 2 == 0)
		usleep(thread->data->time_to_eat * 100);
	while (!is_finish(thread))
	{
		if (philo_eat(thread))
			break ;
		if (philo_action(thread, SLEEPING))
			break ;
		if (philo_action(thread, THINKING))
			break ;
	}
	return (NULL);
}
