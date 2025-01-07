/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:42:11 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/07 20:46:33 by joamiran         ###   ########.fr       */
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
		pthread_mutex_lock(&table->philos[i].n_eat);
		if (table->philos[i].eat_count < table->must_eat_count)
		{
			pthread_mutex_unlock(&table->philos[i].n_eat);
			return (false);
		}
		pthread_mutex_unlock(&table->philos[i].n_eat);
		i++;
	}
	table->all_ate = true;
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
			print_message(&table->philos[i], "died");
			pthread_mutex_unlock(&table->philos[i].n_eat);
			table->simulating = false;
			return (NULL);
		}
		pthread_mutex_unlock(&table->philos[i].n_eat);
		if (table->must_eat_count > 0)
		{
			if (check_all_ate(table))
			{
				table->simulating = false;
				return (NULL);
			}
		}
		usleep(100);
		i++;
		if (i == table->n_philos)
			i = 0;
	}
	return (NULL);
}
