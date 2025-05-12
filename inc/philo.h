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

/* ============================= CLEAN ==================================== */
int					print_error(char *msg);
int					free_error(t_data *data, char *msg);
void				print_state(t_data *data, int id, char *state);
void				cleanup(t_data *data, t_thread *thread);

/* ============================= INIT_DATA ================================= */
int					init_args(t_data *data, int ac, char **av);
t_forks				*init_forks(t_data *data);
t_thread			*init_thread(t_data *data);
t_data				init_data(t_data *data, int ac, char **av);

/* ============================= START_PROCESS ============================= */
int					start_process(t_data *data);

/* ============================= THREAD_ACTION ============================= */
int					is_finish(t_thread *thread);
void				*thread_action(void *arg);

/* ============================= THREAD_MONITOR ============================ */
int					check_philosopher_death(t_data *data, int i);
int					check_meal_completion(t_data *data);
void				*monitor_process(void *arg);

/* ============================= THREAD_UTILS ============================== */
void				set_fork_order(t_thread *thread, int *r_fork, int *l_fork);
int					take_forks(t_thread *thread, int right_fork, int left_fork);
void				release_forks(t_data *data, int right_fork, int left_fork);
void				update_meal_time(t_thread *thread);

/* ============================== UTILS ==================================== */
int					is_number(char *str);
int					ft_atoi(const char *str);
long				get_time(void);
void				ft_sleep(long time);

#endif
