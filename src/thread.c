/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:18:28 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/06 21:38:16 by joamiran         ###   ########.fr       */
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
	int		right_fork;
	int		left_fork;

	philo = (t_philo *)arg;
	right_fork = philo->right_fork;
	left_fork = philo->left_fork;
	while (philo->table->simulating)
	{
        if (philo->id % 2 == 0)
            grab_forks(philo);
        if (philo->id % 2 != 0)
            philo_think(philo);
        if (philo->id % 2 == 0)
            philo_eat(philo);
        if (philo->id % 2 != 0)
            grab_forks(philo);
        if (philo->id % 2 == 0)
            philo_sleep(philo);
        if (philo->id % 2 != 0)
            philo_eat(philo);
        if (philo->id % 2 == 0)
            philo_think(philo);
        if (philo->id % 2 != 0)
            philo_sleep(philo);
	}
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
	while (i < table->n_philos)
	{
		pthread_join(table->thread_array[i], NULL);
		i++;
	}
}

// start threading
void	start_threading(t_table *table)
{
	create_threads(table);
	if (pthread_create(table->controler, NULL, sim_controler, table) != 0)
	{
		free_thread_array(table);
		print_error("Error creating controler thread");
        return ;
	}
	join_threads(table);
	pthread_join(*table->controler, NULL);
}
