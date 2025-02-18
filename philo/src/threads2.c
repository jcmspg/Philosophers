/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:29:07 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/18 22:14:41 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// routine for the philosophers
#include "../philo.h"

void	*eat_pray_love(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_sync(philo->table);
	if (philo->id % 2 == 0)
		usleep(10);
	while (simulating(philo->table))
	{
		if (check_if_dead(philo))
			return (NULL);
		if (philo->full)
			return (NULL);
		eat(philo);
		sleeperino(philo);
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
