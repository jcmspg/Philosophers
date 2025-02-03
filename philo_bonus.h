/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:36:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/03 21:48:21 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "philo.h"
# include <complex.h>

// defines
# define SEM_FORK_NAME "/fork_sem"

// structs
typedef struct s_philo_bonus
{
	int						id;
	int						eat_count;
	long					last_eat;

	sem_t					*left_fork;
	sem_t					*right_fork;
	sem_t					*sem_print;

	bool					is_dead;
	bool					full;

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

	sem_t					*sem_forks;
	sem_t					*sem_print;
	t_philo_b				**philos;
}							t_table_b;

// functions
// bonus

// main

// validations
t_table_b					*validation_initialization_b(int argc, char **argv);
bool						check_eat_count_b(t_table_b *table);
bool						check_time_b(t_table_b *table);
bool						check_philos_b(t_table_b *table);
bool						check_values_b(t_table_b *table);

// init
bool						populate_b(t_table_b *table, char **argv);
t_table_b					*init_table_b(char **argv);

// utils
void						assign_values_b(t_table_b *table, char **argv);

// simulation

// philos
t_table_b					*create_philo(t_table_b *table, int id);
void						create_philos(t_table_b *table);
void						forking_philos(t_table_b *table);

// verfications
bool						check_death_sem(t_philo_b *philo);
bool						check_end(t_philo_b *philo);

// philo_life
void						philo_life_sem(t_philo_b *philo);
void						think_sem(t_philo_b *philo);
void						eat_sem(t_philo_b *philo);
void						sleep_sem(t_philo_b *philo);

// time
long						get_timestamp_b(t_table_b *table);
void						print_formatted_timestamp_b(long timestamp);
void						ft_start_time_b(t_table_b *table);
void						print_message_b(t_philo_b *philo, char *msg);

// free
void						free_table_b(t_table_b *table);

#endif
