/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:19:00 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/22 20:30:01 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// initialize the table
t_table	*init_table(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
	{
		print_error("Error allocating memory");
		return (NULL);
	}
	memset(table, 0, sizeof(t_table));
	if (!validate_numbers(argv))
	{
		free(table);
		print_error("Invalid arguments");
		return (NULL);
	}
	assign_values(table, argv);
	if (!check_philos(table) || !check_time(table) || !check_eat_count(table))
	{
		free(table);
		print_error("Invalid arguments");
		return (NULL);
	}
	table->simulating = false;
	table->ready_set_go = false;
	table->all_ate = false;
	table->thread_array = NULL;

	table->philos = autobots_assemble(table);
	if (!table->philos)
	{
		free(table);
		print_error("Error creating philosophers");
		return (NULL);
	}
	init_forks(table);
		if (!table->forks)
	{
		print_error("Error initializing mutexes");
		free_table(table);
		return (NULL);
	}
	table->thread_array= init_thread_array(table);
	return (table);
}