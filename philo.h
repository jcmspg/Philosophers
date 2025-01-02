/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:36:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/02 21:40:18 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

// defines
#define MAX_PHILOS INT_MAX
#define MIN_PHILOS 2

#define MAX_TIME INT_MAX
#define MIN_TIME 1

#define MAX_EAT_COUNT INT_MAX
#define MIN_EAT_COUNT 0

#define MAX_ARGS 6
#define MIN_ARGS 5



// structs

// philosopher struct
typedef struct s_philo
{
	int			    id;                 // starts at 1 (1 to n)-> number of philosopher
	int			    eat_count;          // starts   // starts at 0 -> number of times the philosopher ate
	int			    last_eat;           // starts   // last time the philosopher ate -> in ms

    
    int             right_fork;                     // starts   // right fork -> number of the fork
    int             left_fork;                      // starts   // left fork -> number of the fork
}				    t_philo;

// table struct
typedef struct s_table
{
	int			n_philos;           // number of philosophers
    int         n_forks;            // number of forks
    int			time_to_die;        // time to die in ms
	int			time_to_eat;        // time to eat in ms
	int			time_to_sleep;      // time to sleep in ms
	int			must_eat_count;     // number of times each philosopher must eat
    
    pthread_t   *controler;         // thread to check if a philo died or if all philos ate
    char   **thread_array;     // array of threads for each philosopher
    
    pthread_mutex_t *forks;         // array of forks

    t_philo		**philos;            // array of philosophers
}				t_table;

// functions
// main.c
int     main(int argc, char **argv);

// validate.c
bool        check_eat_count(t_table *table);
bool        check_time(t_table *table);
bool        check_philos(t_table *table);
bool        validate_numbers(char **argv);
bool        validate_args(int argc, char **argv);

// init.c
t_table     *init_table(char **argv);

// philo_maker.c
void        free_philos(t_table *table);
t_philo     *create_philo(int id);
t_philo     **autobots_assemble(t_table *table);

// sim.c
void        start_sim(t_table *table);

// thread.c
void        *philo_life(t_philo *philo);
pthread_t   create_thread(t_philo *philo);
void        join_threads(t_table *table);
void        create_threads(t_table *table);

// aux.c
bool        ft_isnumber(char *str);
int         ft_atoi(const char *str);
void        assign_values(t_table *table, char **argv);

// error.c
int         print_error(char *msg);
void        print_info(t_philo *philo);
void        print_all(t_table *table);
void        free_table(t_table *table);


#endif
