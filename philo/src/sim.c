/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:09:59 by joao              #+#    #+#             */
/*   Updated: 2025/02/18 19:31:20 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// waiting for sync so all threads start at the same time
void	set_sync(t_table *table)
{
	while (!check_bool(&table->table, &table->ready_set_go))
	{
		usleep(100);
	}
}

void	sim_one(t_table *table)
{
	create_threads(table);
	handle_bool(&table->table, &table->ready_set_go, true);
	handle_bool(&table->table, &table->simulating, true);
	join_threads(table);
}

void	start_sim(t_table *table)
{
	ft_start_time(table);
	if (table->n_philos == 1)
	{
		sim_one(table);
	}
	else
	{
		table->time_to_think = ((table->time_to_eat * 2)
				- table->time_to_sleep);
		create_threads(table);
		handle_bool(&table->table, &table->ready_set_go, true);
		handle_bool(&table->table, &table->simulating, true);
		join_threads(table);
	}
}
