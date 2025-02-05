/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:36:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/05 21:10:52 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

// defines
# define MAX_PHILOS 200
# define MIN_PHILOS 1

# define MAX_TIME INT_MAX
# define MIN_TIME 60

# define MAX_EAT_COUNT INT_MAX
# define MIN_EAT_COUNT -1

# define MAX_ARGS 6
# define MIN_ARGS 5

// defines
# define SEM_FORK_L_NAME "left_fork"
# define SEM_FORK_R_NAME "right_fork"
# define SEM_PRINT_NAME "sem_print"
# define SEM_EXTRA_NAME "extra"
// structs
typedef struct s_philo_bonus
{
	int						id;
	int						eat_count;
	long					last_eat;

	pid_t					philos_pid;

	bool					is_dead;
	bool					full;

	pthread_t				thread;
	struct s_table_bonus	*table;
}							t_philo_b;

// bonus structs
typedef struct s_table_bonus
{
	int						n_philos;
	int						round;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	int						must_eat_count;
	int						eat_count;
	bool					simulating;
	bool					all_ate;

	struct timeval			start_time;

	pthread_mutex_t			print;

    sem_t                   *extra;
	sem_t					*right_fork;
	sem_t					*left_fork;
	sem_t					*sem_print;
	t_philo_b				**philos;
}							t_table_b;

// functions
// bonus

// main
int							main(int argc, char **argv);

// validations
t_table_b					*validation_initialization_b(int argc, char **argv);
bool						check_eat_count_b(t_table_b *table);
bool						check_time_b(t_table_b *table);
bool						check_philos_b(t_table_b *table);
bool						check_values_b(t_table_b *table);
bool						validate_numbers(char **argv);
bool						validate_args(int argc, char **argv);
void						init_semaphores(t_table_b *table);

// init
bool						populate_b(t_table_b *table, char **argv);
bool						prepare_numbers(char **argv);
t_table_b					*init_table_b(char **argv);

// utils
void						assign_values_b(t_table_b *table, char **argv);
void						print_philo(t_philo_b *philo, char *msg);

// error
int							print_error_b(char *msg);
void						print_table_info_b(t_table_b *table);
void						print_info_b(t_philo_b *philo);
void						print_all_info_b(t_table_b *table);
void						print_results_b(t_table_b *table);

// simulation
void						*eat_pray_love_b(void *arg);
void						monitor(t_philo_b *philo);

// semaphores
void						print_sem(t_philo_b *philo, char *msg);
void						think_sem(t_philo_b *philo);
bool						check_death_sem(t_philo_b *philo);
bool						check_end(t_philo_b *philo);
void						eat_sem(t_philo_b *philo);
void						sleep_sem(t_philo_b *philo);
void						philo_life_sem(t_philo_b *philo);

// philos
t_philo_b					*create_philo_b(t_table_b *table, int id);
void						create_philos_b(t_table_b *table);
void						forking_philos_b(t_table_b *table);
void						wait_philos_b(t_table_b *table);

// verfications
bool						check_death_sem(t_philo_b *philo);
bool						check_end(t_philo_b *philo);

// time
void						check_timeval_b(struct timeval *time,
								t_table_b *table);
long						get_timestamp_b(t_table_b *table);
void						ft_start_time_b(t_table_b *table);
void						print_message_b(t_philo_b *philo, char *msg);
void						print_formatted_timestamp_b(long timestamp);

// free
void						free_table_b(t_table_b *table);
void wrap_up(t_table_b *table);

// utils
size_t						ft_strlen(const char *str);
int							ft_atoi(const char *str);
bool						ft_isnumber(char *str);
void						assign_values_b(t_table_b *table, char **argv);

#endif
