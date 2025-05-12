/* ============================= UTILS ============================= */

#include "../inc/philo.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(long time)
{
	long	start;
	long	remaining;
	long	current;
	long	sleep_time;

	start = get_time();
	while (1)
	{
		current = get_time();
		if ((current - start) >= time)
			break ;
		remaining = time - (current - start);
		if (remaining < 2)
			continue ;
		sleep_time = remaining;
		if (remaining > 10)
			sleep_time = remaining - 10;
		usleep(sleep_time * 800);
	}
}
