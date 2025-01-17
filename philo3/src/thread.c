/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:18:28 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/17 16:43:37 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <sys/select.h>

// free thread array
void	free_thread_array(t_table *table)
{
	if (!table->thread_array)
		return ;
	free(table->thread_array);
}

// create thread array
pthread_t	*create_thread_array(t_table *table)
{
	pthread_t	*thread_array;

	thread_array = malloc(sizeof(pthread_t) * table->n_philos);
	if (!thread_array)
		print_error("Error creating thread array");
	return (thread_array);
}

// create thread
pthread_t	create_thread(t_philo *philo)
{
    pthread_t	thread;

    if (pthread_create(&thread, NULL, philo_life, philo))
    {
        free_thread_array(philo->table);
        print_error("Error creating thread");
    }
    return (thread);
}

// create threads
void	create_threads(t_table *table)
{
    int	i;

    i = 0;
    while (i < table->n_philos)
    {
        table->thread_array[i] = create_thread(&table->philos[i]);
        i++;
    }
}


// join threads
void	join_threads(t_table *table)
{
	int	i;

	i = 0;

    pthread_mutex_lock(&table->control);
    table->simulating = true; 
    pthread_mutex_unlock(&table->control);

    while (i < table->n_philos)
	{
		pthread_join(table->thread_array[i], NULL);
		i++;
	}

}

void *philo_life(void *arg)
{
    t_philo	*philo;

    philo = (t_philo *)arg;
    while (philo->table->simulating)
    {
        grab_forks(philo);
        eat(philo);
        release_forks(philo);
        sleep_philo(philo);
        print_message(philo, "is thinking");
    }
    return (NULL);
}



// start threading
void	start_threading(t_table *table)
{
	create_threads(table);
	join_threads(table);
}
