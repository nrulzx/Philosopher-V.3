/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flash19 <flash19@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by flash19           #+#    #+#             */
/*   Updated: 2023/01/01 00:00:00 by flash19          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_args(t_data *data, int ac, char **av)
{
	data->philo_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	data->someone_died = false;
	data->all_ate = false;
	data->start_time = get_time();
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (print_error("Error: Failed to initialize print mutex\n"));
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (print_error("Error: Failed to initialize death mutex\n"));
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		return (print_error("Error: Failed to initialize meal mutex\n"));
	}
	return (0);
}

t_forks	*init_forks(t_data *data)
{
	t_forks	*forks;
	int		i;

	forks = (t_forks *)malloc(sizeof(t_forks) * data->philo_num);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->philo_num)
	{
		forks[i].id = i;
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i].mutex);
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_thread	*init_thread(t_data *data)
{
	t_thread	*threads;
	int			i;

	threads = (t_thread *)malloc(sizeof(t_thread) * data->philo_num);
	if (!threads)
		return (NULL);
	i = 0;
	while (i < data->philo_num)
	{
		threads[i].id = i + 1;
		threads[i].last_meal = get_time();
		threads[i].meals_count = 0;
		threads[i].state = THINKING;
		threads[i].data = data;
		threads[i].right_fork = i;
		threads[i].left_fork = (i + 1) % data->philo_num;
		i++;
	}
	return (threads);
}

static void	cleanup_init_failure(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->philo_num)
			pthread_mutex_destroy(&data->forks[i++].mutex);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	data->forks = NULL;
	data->threads = NULL;
}

t_data	init_data(t_data *data, int ac, char **av)
{
	if (init_args(data, ac, av) != 0)
		return (*data);
	data->forks = init_forks(data);
	if (!data->forks)
	{
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		pthread_mutex_destroy(&data->meal_mutex);
		data->forks = NULL;
		return (*data);
	}
	data->threads = init_thread(data);
	if (!data->threads)
	{
		cleanup_init_failure(data);
	}
	return (*data);
}
