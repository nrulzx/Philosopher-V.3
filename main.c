#include "inc/philo.h"

int	check_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (print_error("Error: Invalid number of arguments\n"));
	i = 1;
	while (i < ac)
	{
		if (!is_number(av[i]))
			return (print_error("Error: Arguments must be positive numbers\n"));
		i++;
	}
	if (ft_atoi(av[1]) <= 0)
		return (print_error("Error: There must be at least one philosopher\n"));
	if (ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return (print_error("Error: Time values must be positive\n"));
	if (ac == 6 && ft_atoi(av[5]) <= 0)
		return (print_error("Error: Number of meals must be positive\n"));
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av))
		return (1);
	init_data(&data, ac, av);
	if (!data.forks || !data.threads)
		cleanup(&data, NULL);
	start_process(&data);
	cleanup(&data, data.threads);
	return (0);
}
