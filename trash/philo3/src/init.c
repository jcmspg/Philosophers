/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:19:00 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/17 18:01:50 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// initialize the table
t_table	*init_table(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	if (!validate_numbers(argv))
	{
		free(table);
		return (NULL);
	}
	assign_values(table, argv);
	if (!check_philos(table) || !check_time(table) || !check_eat_count(table))
	{
		free(table);
		return (NULL);
	}
	if (table->must_eat_count >= 0)
		init_eat_count(table);
	table->simulating = false;
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->control, NULL);
	return (table);
}

// free table
void	free_table(t_table *table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	if (table->philos)
		free_philos(table);
	pthread_mutex_destroy(&table->write);
	if (table->thread_array)
	{
		free_thread_array(table);
	}
	if (table->forks)
		free_forks(table);
	if (table->eat_count)
		free(table->eat_count);
	if (table->n_eat)
		free_eat_count_mutexes(table);
	if (table)
		free(table);
}

void	init_eat_count(t_table *table)
{
	int	i;

	i = 0;
	table->eat_count = malloc(sizeof(int) * table->n_philos);
	if (!table->eat_count)
	{
		print_error("Error creating eat count");
		return ;
	}
	memset(table->eat_count, 0, sizeof(int) * table->n_philos);

    init_eat_count_mutexes(table);
}
