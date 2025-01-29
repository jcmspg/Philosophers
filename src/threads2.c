/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:29:07 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 20:14:18 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// routine for the philosophers
#include "../philo.h"

void	*eat_pray_love(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_sync(philo->table);
	while (simulating(philo->table) && !check_if_dead(philo))
	{
		if (check_bool(&philo->table->table, &philo->full))
			return (NULL);
		eat(philo);
		if (check_bool(&philo->table->table, &philo->full))
			return (NULL);
		sleeperino(philo);
		if (check_bool(&philo->table->table, &philo->full))
			return (NULL);
		think(philo);
	}
	return (NULL);
}

// function to join all threads
void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_join(table->thread_array[i], NULL);
		i++;
	}
}

pthread_t	create_thread(t_philo *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, eat_pray_love, philo))
	{
		free_thread_array(philo->table);
		print_error("Error creating thread");
		return (0);
	}
	return (thread);
}

// start simulation
void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->thread_array[i] = create_thread(&table->philos[i]);
		if (table->thread_array[i] == 0)
			return ;
		i++;
	}
}
