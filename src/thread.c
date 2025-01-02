/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:18:28 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/02 21:40:15 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void   *philo_life(t_philo *philo)
{
    //wait 5 seconds
    printf("Philosopher nbr: %d waiting for 5 seconds.\n", philo->id);
    sleep(5);
    printf("Philosopher nbr: %d waited.\n", philo->id);
    return (NULL);
}
 
char **create_thread_array(t_table *table)
{
    char **thread_array;

    thread_array = malloc(sizeof(char *) * (table->n_philos + 1));
    if (!thread_array)
        return (NULL);
    memset(thread_array, 0, sizeof(char *) * table->n_philos);
    return (thread_array);
}

void    create_threads(t_table *table)
{
    int i;
    

    i = 0;
    table->thread_array = create_thread_array(table);

    while (i < table->n_philos)
    {
        table->thread_array[i] = malloc(sizeof(char) * 10);
        if (!table->thread_array[i])
            return ;
        memset(table->thread_array[i], 0, sizeof(char) * 10);
        sprintf(table->thread_array[i], "Thread %d", i);
        pthread_create(&table->thread_array[i], NULL, (void *)philo_life, table->philos[i]);
        i++;
    }
}

void    start_threading(t_table *table)
{
    create_threads(table);
    join_threads(table);
}
