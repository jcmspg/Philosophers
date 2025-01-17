/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:19:20 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/17 21:24:49 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../philo.h"

// initialize mutexes
void init_table_mutexes(t_table *table)
{
    int	i;

    i = 0;
    while (i < table->n_forks)
    {
        if (pthread_mutex_init(&table->forks[i], NULL))
        {
            (print_error("Mutex init failed"));
            return ;
        }
        i++;
    }
    if (pthread_mutex_init(&table->write, NULL))
    {
        (print_error("Mutex init failed"));
        return ;
    }
}

// destroy mutexes
void destroy_table_mutexes(t_table *table)
{
    int	i;

    i = 0;
    while (i < table->n_forks)
    {
        if (pthread_mutex_destroy(&table->forks[i]))
        {
            (print_error("Mutex destroy failed"));
            return ;
        }
        i++;
    }
    if (pthread_mutex_destroy(&table->write))
    {
        (print_error("Mutex destroy failed"));
        return ;
    }
}

