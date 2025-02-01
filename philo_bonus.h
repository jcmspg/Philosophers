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
#include <complex.h>

// structs
typedef struct s_philo_bonus
{
	int						id;
	int						eat_count;
	long					last_eat;

	bool                    can_eat;
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
	int                     group_size;
	bool					simulating;
	bool					all_ate;

	struct timeval			start_time;

	int                     *eating_indexes;
	sem_t					*semaphore;

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

// init
bool						populate_b(t_table_b *table, char **argv);
bool						prepare_philos_b(t_table_b *table);
t_table_b					*init_table_b(char **argv);

// cycling
int                        *prepare_eating(t_table_b *table);
bool                        set_eating_indexes(t_table_b *table);
void    roatate_eating_group(t_table_b *table, int round);

// philo
void						init_philo_b(t_table_b *table, int id);
t_philo_b					*autobots_assemble_b(t_table_b *table);
void forking_philos(t_table_b *table);

// utils
void						assign_values_b(t_table_b *table, char **argv);

//simulation
bool                        start_simulation(t_table_b *table);


// philos
t_table_b                    *create_philo(t_table_b *table, int id);
void                        create_philos(t_table_b *table);

// philo_life
void                        philo_life_b(t_philo_b *philo);

// semaphores
void						init_semaphore(t_table_b *table);
void                        start_semaphore(t_table_b *table);
void                        cleanup_semaphore(t_table_b *table);


// time
long                        get_timestamp_b(t_table_b *table);
void                       print_formatted_timestamp_b(long timestamp);
void                        ft_start_time_b(t_table_b *table);
void                        print_message_b(t_philo_b *philo, char *msg);


// free
void                        free_table_b(t_table_b *table);

#endif
