/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:25:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/30 17:57:13 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_t	*init_thread_array(t_table *table)
{
	pthread_t	*thread_array;

	thread_array = malloc(sizeof(pthread_t) * table->n_philos);
	if (!thread_array)
		return (NULL);
	memset(thread_array, 0, sizeof(pthread_t) * table->n_philos);
	return (thread_array);
}

bool	check_if_dead(t_philo *philo)
{
	long	current_time;

	current_time = get_timestamp(philo->table);
	if (current_time - philo->last_eat >= philo->table->time_to_die)
	{
		print_message(philo, "died");
		handle_bool(&philo->table->philo_mutex, &philo->table->simulating,
			false);
		handle_bool(&philo->table->death_mutex, &philo->is_dead, true);
		return (true);
	}
	return (false);
}

bool	has_lower_eat_count(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->table->philo_mutex);
	while (i < philo->table->n_philos)
	{
		if (philo->eat_count > philo->table->philos[i].eat_count)
		{
			pthread_mutex_unlock(&philo->table->philo_mutex);
			return (true);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->table->philo_mutex);
	return (false);
}

// functon to see if the philo eat count is higher than the others
bool	check_all_ate(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->table->philo_mutex);
	while (i < philo->table->n_philos)
	{
		if (philo->eat_count > philo->table->philos[i].eat_count)
		{
			pthread_mutex_unlock(&philo->table->philo_mutex);
			return (false);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->table->philo_mutex);
	return (true);
}
