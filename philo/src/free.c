/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:10:50 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 16:09:17 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// free the forks
void	free_forks(t_table *table)
{
	int	i;

	if (!table->forks)
	{
		printf("forks is null\n");
		return ;
	}
	i = 0;
	while (i < table->n_forks)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

void	free_philos(t_table *table)
{
	if (!table->philos)
		return ;
	free(table->philos);
}

void	free_thread_array(t_table *table)
{
	if (!table->thread_array)
		return ;
	free(table->thread_array);
}

// free table
void	free_table(t_table *table)
{
	if (!table)
	{
		printf("table is null\n");
		return ;
	}
	if (!table->philos)
	{
		printf("philos is null\n");
		return ;
	}
	else if (table->philos)
		free_philos(table);
	if (table->thread_array)
		free_thread_array(table);
	if (table->forks)
		free_forks(table);
	if (table)
		free(table);
}
