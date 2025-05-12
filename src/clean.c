/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flash19 <flash19@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by flash19           #+#    #+#             */
/*   Updated: 2023/01/01 00:00:00 by flash19          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	print_error(char *msg)
{
	printf("%s", msg);
	return (1);
}

int	free_error(t_data *data, char *msg)
{
	if (data)
		free(data);
	printf("%s\n", msg);
	return (1);
}

void	print_state(t_data *data, int id, char *state)
{
	long	current_time;

	pthread_mutex_lock(&data->print_mutex);
	current_time = get_time() - data->start_time;
	pthread_mutex_lock(&data->death_mutex);
	if (!data->someone_died || state[0] == 'd')
		printf("%ld %d %s\n", current_time, id, state);
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->print_mutex);
}

void	cleanup(t_data *data, t_thread *thread)
{
	int	i;

	if (thread)
		join_threads(data);
	if (data->forks)
	{
		i = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_destroy(&data->forks[i].mutex);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	if (data->threads)
		free(data->threads);
}
