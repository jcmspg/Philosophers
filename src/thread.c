/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:18:28 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/03 20:55:16 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//free thread array
void    free_thread_array(t_table *table)
{
    if (!table->thread_array)
        return ;
    free(table->thread_array);
}


// routine to execute by each thread
void   *philo_life(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg; //cast arg to t_philo
    //wait 5 seconds
    printf("Philosopher nbr: %d waiting for 5 seconds.\n", philo->id);
    sleep(5);
    printf("Philosopher nbr: %d waited.\n", philo->id);
    free(philo);
    return (NULL);
}

//create thread array
pthread_t   *create_thread_array(t_table *table)
{
    pthread_t *thread_array;

    thread_array = malloc(sizeof(pthread_t) * table->n_philos);
    if (!thread_array)
        print_error("Error creating thread array");
    return (thread_array);
}

//create thread
void create_threads(t_table *table)
{
    int i;
    t_philo *philo_copy;

    i = 0;
    
    while (i < table->n_philos)
    {
        philo_copy = malloc(sizeof(t_philo));
        if (!philo_copy)
            print_error("Error creating thread");
        *philo_copy = table->philos[i];
        if (pthread_create(&table->thread_array[i], NULL, philo_life, philo_copy))
        {
            free(philo_copy);
            print_error("Error creating thread");
        }
        i++;
    }
}

//join threads
void    join_threads(t_table *table)
{
    int i;

    i = 0;
    while (i < table->n_philos)
    {
        pthread_join(table->thread_array[i], NULL);
        i++;
    }
}

//start threading
void    start_threading(t_table *table)
{
    create_threads(table);
    join_threads(table);
}
