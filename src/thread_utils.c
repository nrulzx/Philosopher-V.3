/* ============================= THREAD_UTILS ============================= */

#include "../inc/philo.h"

void	set_fork_order(t_thread *thread, int *r_fork, int *l_fork)
{
	if (thread->id % 2 == 0)
	{
		*r_fork = thread->right_fork;
		*l_fork = thread->left_fork;
	}
	else
	{
		*l_fork = thread->left_fork;
		*r_fork = thread->right_fork;
	}
}

static int	handle_single_philo(t_data *data, int right_fork)
{
	ft_sleep(data->time_to_die + 10);
	pthread_mutex_unlock(&data->forks[right_fork].mutex);
	return (1);
}

int	take_forks(t_thread *thread, int right_fork, int left_fork)
{
	t_data	*data;

	data = thread->data;
	if (is_finish(thread))
		return (1);
	pthread_mutex_lock(&data->forks[right_fork].mutex);
	print_state(data, thread->id, "has taken a fork");
	if (data->philo_num == 1)
		return (handle_single_philo(data, right_fork));
	pthread_mutex_lock(&data->forks[left_fork].mutex);
	print_state(data, thread->id, "has taken a fork");
	return (0);
}

void	release_forks(t_data *data, int right_fork, int left_fork)
{
	pthread_mutex_unlock(&data->forks[right_fork].mutex);
	pthread_mutex_unlock(&data->forks[left_fork].mutex);
}

void	update_meal_time(t_thread *thread)
{
	pthread_mutex_lock(&thread->data->meal_mutex);
	thread->last_meal = get_time();
	thread->meals_count++;
	pthread_mutex_unlock(&thread->data->meal_mutex);
}
