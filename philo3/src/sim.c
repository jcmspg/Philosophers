/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:42:11 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/16 19:38:17 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// start the simulation
void	start_sim(t_table *table)
{
    ft_start_time(table);
	start_threading(table);
}

// check if all philosophers ate
bool	check_all_ate(t_table *table)
{
    int	i;

    i = 0;

    if (!table->must_eat_count)
        return (false);

    while (i < table->n_philos)
    {
        pthread_mutex_lock(&table->philos[i].n_eat);
        if (table->n_eat[i] < table->must_eat_count)
        {
            pthread_mutex_unlock(&table->philos[i].n_eat);
            return (false);
        }
        pthread_mutex_unlock(&table->philos[i].n_eat);
        i++;
    }
    return (true);
}


// check if philosopher is dead
bool	check_death(t_table *table, t_philo *philo)
{
    long    now;
    long    last_eat;

    now = get_timestamp(table);
    last_eat = philo->last_eat;
    
    if (now - last_eat > table->time_to_die)
    {
        pthread_mutex_lock(&philo->is_dead_mutex);
        if (!philo->is_dead)
        {
            philo->is_dead = true;
            print_message(philo, "died");
        }
        pthread_mutex_unlock(&philo->is_dead_mutex);
        return (true);
    }
    return (false);
}

// function to control the simulation (ate counter, death)
void	*philo_control(void *arg)
{
    t_table	*table;
    int        i;

    table = (t_table *)arg;
    while (table->simulating == true)
    {
        i = 0;
        pthread_mutex_lock(&table->control);
        if (check_death(table, &table->philos[i]))
        {
            table->simulating = false;
            pthread_mutex_unlock(&table->control);
            return (NULL);
        }
        if (table->must_eat_count && check_all_ate(table))
        {
            table->simulating = false;
            pthread_mutex_unlock(&table->control);
            return (NULL);
        }
        pthread_mutex_unlock(&table->control);
        i++;
        usleep(10);
    }
    return (NULL);
}


