/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:19:00 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/08 20:21:39 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	table->controler = malloc(sizeof(pthread_t));
	memset(table->controler, 0, sizeof(pthread_t));
	if (!table->controler)
	{
		free(table);
		return (NULL);
	}
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->control, NULL);
	return (table);
}

void	free_table(t_table *table)
{
    int i;
	if (!table)
		return ;

    i = 0;
	if (table->philos)
		free_philos(table);
    pthread_mutex_destroy(&table->write);
	if (table->thread_array)
    {
        while (i < table->n_philos)
        {
            pthread_mutex_destroy(&table->philos[i].n_eat);
            pthread_mutex_destroy(&table->philos[i].is_dead_mutex);
            i++;
        }
        free_thread_array(table);
    }

	if (table->forks)
    {
        i = 0;
        while (i < table->n_forks)
        {
            pthread_mutex_destroy(&table->forks[i]);
            i++;
        }
        free_forks(table);
    }

	if (table->controler)
    {
        pthread_mutex_destroy(&table->control);
		free(table->controler);
    }

    if (table)
		free(table);
}
