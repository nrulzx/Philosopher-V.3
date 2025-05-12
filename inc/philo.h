#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DIED
}	t_state;

typedef struct s_forks
{
	pthread_mutex_t	mutex;
	int				id;
}					t_forks;

typedef struct s_thread
{
	pthread_t		thread;
	int				id;
	long			last_meal;
	int				meals_count;
	int				right_fork;
	int				left_fork;
	t_state			state;
	struct s_data	*data;
}					t_thread;

typedef struct s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	bool			someone_died;
	bool			all_ate;
	long			start_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	t_forks			*forks;
	t_thread		*threads;
}					t_data;

/* ========================== clean.c ========================== */
int					print_error(char *msg);
int					free_error(t_data *data, char *msg);
void				print_state(t_data *data, int id, char *state);
void				cleanup(t_data *data, t_thread *thread);

/* ========================= init_data.c ======================== */
int					check_args(int ac, char **av);
int					init_args(t_data *data, int ac, char **av);
t_data				init_data(t_data *data, int ac, char **av);
t_forks				*init_forks(t_data *data);
t_thread			*init_thread(t_data *data);

/* ========================== thread_utils.c ========================== */
int					is_finish(t_thread *thread);
int					handle_single_philo(t_data *data, int right_fork);
void				update_meal_time(t_thread *thread);
void				release_forks(t_data *data, int right_fork, int left_fork);
void				join_threads(t_data *data);

/* ========================== start_process.c ========================== */
int					check_died(t_thread *thread, int time_to_die);
int					check_all_ate(t_data *data);
void				*monitor_process(void *arg);
int					start_process(t_data *data);

/* ========================== thread_action.c ========================== */
int					philo_action(t_thread *thread, t_state state);
void				*thread_action(void *arg);

/* ========================== utils.c ========================== */
int					ft_atoi(const char *str);
int					is_number(char *str);
long				get_time(void);
void				ft_sleep(long time);

#endif
