/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:36:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/27 19:39:30 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <complex.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

// defines
# define MAX_PHILOS INT_MAX
# define MIN_PHILOS 1

# define MAX_TIME INT_MAX
# define MIN_TIME 60

# define MAX_EAT_COUNT INT_MAX
# define MIN_EAT_COUNT 0

# define MAX_ARGS 6
# define MIN_ARGS 5

// structs

// philosopher struct
typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_eat;

	int				right_fork;
	int				left_fork;

	bool			is_dead;
	bool			full;

	struct s_table	*table;
}					t_philo;

// table struct
typedef struct s_table
{
	int				n_philos;
	int				n_forks;
	int				round;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;

	bool			simulating;
	bool			all_ate;
	bool			ready_set_go;

	struct timeval	start_time;

	pthread_t		*thread_array;

	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	table;
	pthread_mutex_t	write;

	pthread_mutex_t	*forks;

	t_philo			*philos;
}					t_table;

// functions
// main.c
int					main(int argc, char **argv);

// validate.c
bool				check_eat_count(t_table *table);

bool				check_time(t_table *table);

bool				check_philos(t_table *table);

bool				check_values(t_table *table);
bool				validate_numbers(char **argv);

bool				validate_args(int argc, char **argv);

bool				check_thread_array(t_table *table);

t_table				*validation_initialization(int argc, char **argv);

// init.c
t_table				*init_table(char **argv);
void				init_forks(t_table *table);

// philo_maker.c
void				free_philos(t_table *table);
t_philo				*create_philo(int id);
t_philo				*autobots_assemble(t_table *table);

// sim.c
void				set_sync(t_table *table);
void				start_sim(t_table *table);

// routine.c

// threads.c
pthread_t			*init_thread_array(t_table *table);
void				eat(t_philo *philo);
void				sleeperino(t_philo *philo);
void				grab_forks(t_philo *philo);
void				think(t_philo *philo);
void				*eat_pray_love(void *data);
void				join_threads(t_table *table);
void				create_threads(t_table *table);
bool				check_all_ate(t_philo *philo);
// mutexes.c
void				init_table_mutexes(t_table *table);
void				destroy_table_mutexes(t_table *table);

// aux.c
bool				ft_isnumber(char *str);

int					ft_atoi(const char *str);

void				assign_values(t_table *table, char **argv);

// time.c
long				get_timestamp(t_table *table);
void				print_formatted_timestamp(long timestamp);
void				ft_start_time(t_table *table);
void				print_message(t_philo *philo, char *msg);

// error.c
int					print_error(char *msg);
void				print_info(t_philo *philo);
void				print_all_info(t_table *table);
void				print_forks(t_philo *philo);
void				print_table_info(t_table *table);
void				print_results(t_table *table);

// forks.c
void				free_forks(t_table *table);

// free.c
void				free_table(t_table *table);
void				free_thread_array(t_table *table);

// data_handlers.c
void				handle_bool(pthread_mutex_t *mutex, bool *status,
						bool newstatus);

bool				check_bool(pthread_mutex_t *mutex, bool *status);

void				handle_int(pthread_mutex_t *mutex, int *status,
						int newstatus);

int					check_int(pthread_mutex_t *mutex, int *status);

void				handle_long(pthread_mutex_t *mutex, long *status,
						long newstatus);

long				check_long(pthread_mutex_t *mutex, long *status);

bool				simulating(t_table *table);

#endif
