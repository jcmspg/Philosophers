/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:19:20 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/27 17:48:17 by joamiran         ###   ########.fr       */
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
            (print_error("fork mutex init failed"));
            return ;
        }
        i++;
    }
    if (pthread_mutex_init(&table->write, NULL))
    {
        (print_error("write mutex init failed"));
        return ;
    }
    if (pthread_mutex_init(&table->table, NULL))
    {
        (print_error("table mutex init failed"));
        return ;
    }
    if (pthread_mutex_init(&table->death_mutex, NULL))
    {
        (print_error("death mutex init failed"));
        return ;
    }
    if (pthread_mutex_init(&table->philo_mutex, NULL))
    {
        (print_error("philo mutex init failed"));
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
            (print_error("fork  mutex destroy failed"));
            return ;
        }
        i++;
    }
    if (pthread_mutex_destroy(&table->write))
    {
        (print_error("write mutex destroy failed"));
        return ;
    }
    if (pthread_mutex_destroy(&table->table))
    {
        (print_error("table mutex destroy failed"));
        return ;
    }
    if (pthread_mutex_destroy(&table->death_mutex))
    {
        (print_error("death mutex destroy failed"));
        return ;
    }
    if (pthread_mutex_destroy(&table->philo_mutex))
    {
        (print_error("philo mutex destroy failed"));
        return ;
    }
}

