/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:36:06 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/30 18:57:28 by joamiran         ###   ########.fr       */
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

// structs

// philosopher struct
typedef struct s_philo
{
	int			id;                 // starts at 1 (1 to n)-> number of philosopher
	int			eat_count;          // starts// starts at 0 -> number of times the philosopher ate
	int			last_eat;           // starts// last time the philosopher ate -> in ms

	pthread_t	thread;             // starts// thread of the philosopher

	struct s_philo *right;          // starts// right fork -> next (circular)
	struct s_philo *left;           // starts// left fork -> previous (circular)
}				t_philo;

// table struct
typedef struct s_table
{
	int			n_philos;           // number of philosophers
	int			time_to_die;        // time to die in ms
	int			time_to_eat;        // time to eat in ms
	int			time_to_sleep;      // time to sleep in ms
	int			must_eat_count;     // number of times each philosopher must eat

	t_philo		*philos;            // array of philosophers
}				t_table;

// functions
// main.c
int     main(int argc, char **argv);

// validate.c
bool    validate_args(int argc, char **argv, t_table *table);

// init.c

// aux.c
int     ft_atoi(const char *str);

// error.c
int     print_error(char *msg);




#endif
