/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:18:28 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/08 20:22:42 by joamiran         ###   ########.fr       */
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
    pthread_mutex_lock(&philo->table->control);
	while (!philo->table->simulating)
    {
        pthread_mutex_unlock(&philo->table->control);
		usleep(100);
        pthread_mutex_lock(&philo->table->control);
    }
    pthread_mutex_unlock(&philo->table->control);
	pthread_mutex_lock(&philo->table->control);
    while (philo->table->simulating)
	{
        pthread_mutex_unlock(&philo->table->control);
        grab_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
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

    pthread_mutex_lock(&table->control);
    table->simulating = true; 
    pthread_mutex_unlock(&table->control);

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
//    if (pthread_create(table->controler, NULL, sim_controler, table))
//    {
//        free_thread_array(table);
//        print_error("Error creating controler thread");
//    }
	join_threads(table);
}
