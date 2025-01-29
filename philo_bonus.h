/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:36:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 21:34:10 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "philo.h"

// structs
typedef struct s_philo_bonus
{
	int						id;
	int						eat_count;
	long					last_eat;

	int						right_fork;
	int						left_fork;

	bool					is_dead;
	bool					full;

	struct s_table_bonus	*table;
}							t_philo_b;

// bonus structs
typedef struct s_table_bonus
{
	int						n_philos;
	int						n_forks;
	int						round;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	int						must_eat_count;

	bool					simulating;
	bool					all_ate;
	bool					ready_set_go;

	struct timeval			start_time;

	pthread_t				*thread_array;

	t_philo_b				*philos;
	sem_t					*semaphore;
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

// init
bool						populate_b(t_table_b *table, char **argv);
bool						prepare_philos_b(t_table_b *table);
t_table_b					*init_table_b(char **argv);

// philo
void						assign_forks_b(t_table_b *table, int id);
void						init_philo_b(t_table_b *table, int id);
t_philo_b					*autobots_assemble_b(t_table_b *table);

// utils
void						assign_values_b(t_table_b *table, char **argv);

// threads
pthread_t					*init_thread_array_b(t_table_b *table);

// semaphores
void						init_semaphores(t_table_b *table);
void                        start_semaphore(t_table_b *table);

// free
void                        free_bonus_table(t_table_b *table);

#endif
