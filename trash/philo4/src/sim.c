/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:09:59 by joao              #+#    #+#             */
/*   Updated: 2025/01/23 23:35:24 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//waiting for sync so all threads start at the same time
void set_sync(t_table *table)
{
    while (!check_bool(&table->table, &table->ready_set_go))
    {
        usleep(100);
    }
}



void start_sim(t_table *table)
{
    //print in red the warning message of the simulation starting
    ft_start_time(table);
    printf("\033[0;31m\n\nSimulation starting...\033[0m\n\n\n");
    create_threads(table);
    handle_bool(&table->table, &table->ready_set_go, true);
    handle_bool(&table->table, &table->simulating, true);
    join_threads(table);
}



