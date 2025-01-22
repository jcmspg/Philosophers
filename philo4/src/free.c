/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:10:50 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/22 17:26:18 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
// free the forks
void	free_forks(t_table *table)
{
    int	i;

    i = 0;
    while (i < table->n_forks)
    {
        if (pthread_mutex_destroy(&table->forks[i]))
        {
            print_error("Mutex destroy failed");
            return ;
        }
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
	{	
		printf("freeing philos\n");
		free_philos(table);
	}

    if (table->thread_array)
	{
		printf("freeing thread array\n");
		free_thread_array(table);
	}
	if (table->forks)
	{
		printf("freeing forks\n");
		free_forks(table);
	}

	if (table)
	{
		printf("freeing table\n");
		free(table);
	}

	printf("table freed\n");
}
