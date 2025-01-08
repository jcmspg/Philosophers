/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:42:11 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/08 20:28:09 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	start_sim(t_table *table)
{
	start_threading(table);
}

// check if all philosophers ate
bool	check_all_ate(t_table *table)
{
	int	i;

	i = 0;
    
	while (i < table->n_philos)
	{
        pthread_mutex_lock(&table->control);
		pthread_mutex_lock(&table->philos[i].n_eat);
		if (table->philos[i].eat_count < table->must_eat_count)
		{
			pthread_mutex_unlock(&table->philos[i].n_eat);
            pthread_mutex_unlock(&table->control);
			return (false);
		}
		pthread_mutex_unlock(&table->philos[i].n_eat);
        pthread_mutex_unlock(&table->control);
		i++;
	}
    pthread_mutex_lock(&table->control);
	table->all_ate = true;
    pthread_mutex_unlock(&table->control);
	return (true);
}

void	*sim_controler(void *arg)
{
	t_table		*table;
	int			i;
	long long	time;

	table = (t_table *)arg;
	i = 0;
	while (table->simulating)
	{
		pthread_mutex_lock(&table->control);
		time = get_timestamp(table);
		pthread_mutex_unlock(&table->control);
		pthread_mutex_lock(&table->philos[i].n_eat);
		if (time - table->philos[i].last_eat > table->time_to_die)
		{
			pthread_mutex_unlock(&table->philos[i].n_eat);
            pthread_mutex_lock(&table->philos[i].is_dead_mutex);
			table->philos[i].is_dead = true;
            pthread_mutex_unlock(&table->philos[i].is_dead_mutex);
            print_message(&table->philos[i], "died");
            pthread_mutex_lock(&table->control);
			table->simulating = false;
            pthread_mutex_unlock(&table->control);
			return (NULL);
		}
		pthread_mutex_unlock(&table->philos[i].n_eat);
        pthread_mutex_lock(&table->control);
		if (table->must_eat_count > 0)
		{
            pthread_mutex_unlock(&table->control);
			if (check_all_ate(table) == true)
            {
                pthread_mutex_lock(&table->control);
                table->simulating = false;
                pthread_mutex_unlock(&table->control);
                return (NULL);
            }
		}
		usleep(10);
		i++;
		if (i == table->n_philos)
			i = 0;
	}
	return (NULL);
}
