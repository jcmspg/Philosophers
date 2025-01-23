/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:14:07 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/15 16:18:17 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// init the fork mutex
void	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_forks);
	memset(table->forks, 0, sizeof(pthread_mutex_t) * table->n_forks);
	if (!table->forks)
	{
		print_error("Error creating forks");
		return ;
	}
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

// init the eat mutex
void	init_eatcount(t_table *table)
{
	int	i;

	table->eat = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	memset(table->eat, 0, sizeof(pthread_mutex_t) * table->n_philos);
	if (!table->eat)
	{
		print_error("Error creating eat counter");
		return ;
	}
	i = 0;
	while (i < table->n_philos)
	{
		if (pthread_mutex_init(&table->eat[i], NULL))
		{
			print_error("Error initializing eat counter");
			free_eat(table);
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

// free the eat mutex
void	free_eat(t_table *table)
{
	int	i;

	i = 0;
	if (!table->eat)
		return ;
	while (i < table->n_philos)
	{
		pthread_mutex_destroy(&table->eat[i]);
		i++;
	}
	free(table->eat);
}
