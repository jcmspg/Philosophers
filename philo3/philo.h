/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:36:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/17 16:26:42 by joamiran         ###   ########.fr       */
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
    
    bool            is_dead;            // starts   // is the philosopher dead?

    int             right_fork;         // starts   // right fork -> number of the fork
    int             left_fork;          // starts   // left fork -> number of the fork

    struct s_table  *table;             // table struct
    pthread_mutex_t n_eat;              // mutex to control the number of times the philosopher ate
    pthread_mutex_t is_dead_mutex;      // mutex to control the death of the philosopher

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
    int         *eat_count;          // number of times each philosopher ate

    bool        simulating;         // is the simulation running?
    bool        all_ate;            // did all philosophers eat?
	struct timeval	start_time;     // start time of the simulatioo

    pthread_t   *thread_array;      // array of threads for each philosopher

    pthread_mutex_t *n_eat;         // array of mutexes to control the number of times each philosopher ate
    pthread_mutex_t write;          // mutex to write
    pthread_mutex_t *forks;         // array of forks
    pthread_mutex_t control;         // mutex to control the deaths

    t_philo		*philos;            // array of philosophers
}				t_table;

// functions
// main.c
int         main(int argc, char **argv);

// validate.c
bool        check_eat_count(t_table *table);            // check if the number of times each philosopher must eat is valid
bool        check_time(t_table *table);                 // check if the time to die, eat and sleep are valid
bool        check_philos(t_table *table);               // check if the number of philosophers is valid
bool        validate_numbers(char **argv);              // check if the arguments are numbers
bool        validate_args(int argc, char **argv);       // check if the number of arguments is valid
t_table     *validation_initialization(int argc, char **argv); // validate and initialize the table
bool        check_thread_array(t_table *table);         // check if the thread array was created

// init.c

void        init_eat_count(t_table *table);             // initialize the eat count
t_table     *init_table(char **argv);                   // initialize the table
void        free_table(t_table *table);                 // free the table


// philo_maker.c
void        free_philos(t_table *table);                // free the philosophers
t_philo     *create_philo(int id);                      // create a philosopher
t_philo     *autobots_assemble(t_table *table);         // create the philosophers

// sim.c
void        start_sim(t_table *table);                  // start the simulation
bool        check_all_ate(t_table *table);              // check if all philosophers ate
bool        check_death(t_table *table, t_philo *philo);// check if a philosopher is dead
void        *philo_control(void *arg);                  // control the simulation



// routine.c
void        grab_forks(t_philo *philo);                 // grab the forks
void        release_forks(t_philo *philo);              // release the forks
void        eat(t_philo *philo);                        // eat
void        sleep_philo(t_philo *philo);                // sleep
void        *philo_life(void *arg);                     // routine to execute
void        eat_pray_love(t_table *table);              // function that runs philo life and philo control
void        print_message(t_philo *philo, char *msg);   // print a message

// thread.c
void        *philo_life(void *arg);                     // routine to execute by each thread

pthread_t   *create_thread_array(t_table *table);       // create the array of threads
pthread_t   create_thread(t_philo *philo);             // create a thread

void        join_threads(t_table *table);               // join the threads
void        start_threading(t_table *table);            // start the threads
void        free_thread_array(t_table *table);          // free the array of threads

// mutexes.c
void init_forks(t_table *table);                        // initialize the forks
void free_forks(t_table *table);                        // free the forks
void free_eat_count_mutexes(t_table *table);                    // free the eat count
void init_eat_count_mutexes(t_table *table);                    // initialize the eat count

// aux.c
bool        ft_isnumber(char *str);                     // check if a string is a number
int         ft_atoi(const char *str);                   // convert a string to an integer
void        assign_values(t_table *table, char **argv); // assign the values to the table

// time.c
long        get_timestamp(t_table *table);              // get the timestamp
void        print_formatted_timestamp(long timestamp);     // print the timestamp
void        ft_start_time(t_table *table);             // start the time

// error.c
int         print_error(char *msg);                     // print an error message
void        print_info(t_philo *philo);                 // print the philosopher info
void        print_all_info(t_table *table);                  // print all the philosophers info
void        print_forks(t_philo *philo);                // print the forks of a philosopher

void        free_table(t_table *table);                 // free the table


#endif
