/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:25:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/18 21:33:51 by joamiran         ###   ########.fr       */
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
		print_dead(philo);
		handle_bool(&philo->table->table, &philo->is_dead, true);
		handle_bool(&philo->table->table, &philo->table->simulating, false);
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

void	standby(t_philo *philo, long time)
{
	long	start;
	long	current;

	start = get_timestamp(philo->table);
	while (1)
	{
		current = get_timestamp(philo->table);
		if (current - philo->last_eat > philo->table->time_to_die)
			check_if_dead(philo);
		if (current - start >= time)
			break ;
		usleep(10);
	}
}
