/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:14:07 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/06 21:21:34 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>

//init the fork mutex
void init_forks(t_table *table)
{
    int i;

    table->forks = malloc(sizeof(pthread_mutex_t) * table->n_forks);
    memset(table->forks, 0, sizeof(pthread_mutex_t) * table->n_forks);
    if (!table->forks)
    {
        print_error("Error creating forks");
        return ;
    }

    i = 0;
    while (i < table->n_forks)
    {
        if (pthread_mutex_init(&table->forks[i], NULL))
        {
            print_error("Error initializing forks");
            free_forks(table);
            return ;
        }
        i++;
    }
}

//free the fork mutex
void free_forks(t_table *table)
{
    int i;

    i = 0;
    if (!table->forks)
        return ;

    while (i < table->n_forks)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->forks);
}
