/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:42:11 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/16 17:28:34 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	start_sim(t_table *table)
{
    ft_start_time(table);
    create_sim_controller(table);
	start_threading(table);
}

// create thread to control the simulation
void	*sim_controler(void *arg)
{
    t_table	*table;

    table = (t_table *)arg;
    while (table->simulating == true)
    {
        //print something in red to debug
        print_message(&table->philos[0],"\033[0;31mSimulating...\033[0m\n");
        check_end_sim(table);
    }
    return (NULL);
}

void create_sim_controller(t_table *table)
{

    if (pthread_create(&table->sim_thread, NULL, sim_controler, table))
        print_error("Error creating simulation controller");
}
