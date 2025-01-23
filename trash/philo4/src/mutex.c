/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:19:20 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/23 20:30:12 by joao             ###   ########.fr       */
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
    if (pthread_mutex_init(&table->table, NULL))
    {
        (print_error("Mutex init failed"));
        return ;
    }
    if (pthread_mutex_init(&table->death_mutex, NULL))
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
    if (pthread_mutex_destroy(&table->table))
    {
        (print_error("Mutex destroy failed"));
        return ;
    }
    if (pthread_mutex_destroy(&table->death_mutex))
    {
        (print_error("Mutex destroy failed"));
        return ;
    }
}

