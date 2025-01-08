/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:18:28 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/08 23:24:58 by joamiran         ###   ########.fr       */
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
    pthread_mutex_lock(&philo->table->write);
	while (philo->table->simulating == false)
    {
        pthread_mutex_unlock(&philo->table->write);
		usleep(100);
        pthread_mutex_lock(&philo->table->write);
    }
    pthread_mutex_unlock(&philo->table->write);

	pthread_mutex_lock(&philo->table->write);
    while (philo->table->simulating == true)
	{
        if (philo->id % 2 != 0)
            usleep(100);
        pthread_mutex_unlock(&philo->table->write);
        grab_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
    pthread_mutex_unlock(&philo->table->write);
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

    pthread_mutex_lock(&table->write);
    table->simulating = true; 
    pthread_mutex_unlock(&table->write);

    while (i < table->n_philos)
	{
		pthread_join(table->thread_array[i], NULL);
		i++;
	}

}

// start threading
void	start_threading(t_table *table)
{
    ft_start_time(table);
	create_threads(table);
	join_threads(table);
}
