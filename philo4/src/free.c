/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:10:50 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/17 22:10:18 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_philos(t_table *table)
{
	if (!table->philos)
		return ;
	free(table->philos);
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
	
//    if (table->thread_array)
//	{
//		free_thread_array(table);
//	}
	if (table->forks)
		free_forks(table);

	if (table)
		free(table);
}
