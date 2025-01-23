/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:14:07 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/17 16:28:28 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <bits/pthreadtypes.h>

// init the fork mutex
void	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_forks);
	if (!table->forks)
	{
		print_error("Error creating forks");
		return ;
	}
	memset(table->forks, 0, sizeof(pthread_mutex_t) * table->n_forks);
	i = 0;
	while (i < table->n_forks)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			print_error("Error initializing forks");
			free_forks(table);
			return ;
		}
		i++;
	}
}

// free the fork mutex
void	free_forks(t_table *table)
{
	int	i;

	i = 0;
	if (!table->forks)
		return ;
	while (i < table->n_forks)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

void	free_eat_count_mutexes(t_table *table)
{
	int	i;

	i = 0;
	if (!table->n_eat)
		return ;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->n_eat[i]);
		i++;
	}
	free(table->n_eat);
}

// init the eat count array
void	init_eat_count_mutexes(t_table *table)
{
	int	i;

	i = 0;
	table->n_eat = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	if (!table->n_eat)
	{
		print_error("Error creating eat count");
		return ;
	}
	memset(table->n_eat, 0, sizeof(pthread_mutex_t) * table->n_philos);
	while (i < table->n_philos)
	{
		if (pthread_mutex_init(&table->n_eat[i], NULL))
		{
			print_error("Error initializing eat count");
			free_eat_count_mutexes(table);
			return ;
		}
		i++;
	}
}
