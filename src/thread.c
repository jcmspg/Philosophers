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
#include <stdio.h>
#include <sys/select.h>

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
    int right_fork;
    int left_fork;

    philo = (t_philo *)arg; //cast arg to t_philo
    right_fork = philo->right_fork;
    left_fork = philo->left_fork;

    print_formatted_timestamp(get_timestamp(philo->table));
    printf("Philosopher %d is thinking\n", philo->id);
    usleep(1000);

    //try to get the forks
    pthread_mutex_lock(&philo->table->forks[right_fork]);
    print_formatted_timestamp(get_timestamp(philo->table));
    printf("Philosopher %d has taken the right fork\n", philo->id);
    pthread_mutex_lock(&philo->table->forks[left_fork]);
    print_formatted_timestamp(get_timestamp(philo->table));
    printf("Philosopher %d has taken the left fork\n", philo->id);

    //eat
    print_formatted_timestamp(get_timestamp(philo->table));
    printf("Philosopher %d is eating\n", philo->id);
    philo->last_eat = get_timestamp(philo->table);
    usleep(philo->table->time_to_eat * 1000);
    philo->eat_count++;

    //release the forks
    pthread_mutex_unlock(&philo->table->forks[right_fork]);
    pthread_mutex_unlock(&philo->table->forks[left_fork]);

    //sleep
    print_formatted_timestamp(get_timestamp(philo->table));
    printf("Philosopher %d is sleeping\n", philo->id);
    usleep(philo->table->time_to_sleep * 1000);

    //think
    print_formatted_timestamp(get_timestamp(philo->table));
    printf("Philosopher %d is thinking\n", philo->id);

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

    i = 0;

    while (i < table->n_philos)
    {
        if (pthread_create(&table->thread_array[i], NULL, philo_life, &table->philos[i]))
        {
            free(table->thread_array);
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
