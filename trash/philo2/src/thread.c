/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:18:28 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/16 17:33:34 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>
#include <sys/select.h>

// free thread array
void	free_thread_array(t_table *table)
{
	if (!table->thread_array)
		return ;
	free(table->thread_array);
}

// routine to execute by each thread
void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

    sim_controler(philo->table);
	
    while (philo->table->simulating == false)
		usleep(100);
	while (philo->table->simulating == true) 
		eat_pray_love(philo);
	return (NULL);
}

// create thread array
pthread_t	*create_thread_array(t_table *table)
{
	pthread_t	*thread_array;

	thread_array = malloc(sizeof(pthread_t) * table->n_philos);
	if (!thread_array)
		print_error("Error creating thread array");
	return (thread_array);
}

// create thread
void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_create(&table->thread_array[i], NULL, philo_life,
				&table->philos[i]))
		{
			free(table->thread_array);
			print_error("Error creating thread");
		}
		i++;
	}
}

// join threads
void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	table->simulating = true;
	while (i < table->n_philos)
	{
		pthread_join(table->thread_array[i], NULL);
		i++;
	}
    pthread_join(table->sim_thread, NULL);
}

// start threading
void	start_threading(t_table *table)
{
	create_threads(table);
	join_threads(table);
}
