/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:19:00 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/23 23:23:44 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// assigning values
bool	populate(t_table *table, char **argv)
{
	assign_values(table, argv);
	if (!check_values(table))
	{
		free(table);
		print_error("Invalid values");
		return (false);
	}
	table->simulating = false;
	table->ready_set_go = false;
	table->all_ate = false;
	table->thread_array = NULL;
	table->forks = NULL;
	table->philos = NULL;
	return (true);
}

bool	prepare_philos(t_table *table)
{
	table->philos = autobots_assemble(table);
	if (!table->philos)
	{
		free(table);
		print_error("Error creating philosophers");
		return (false);
	}
	init_forks(table);
	if (!table->forks)
	{
		print_error("Error initializing mutexes");
		free_table(table);
		return (false);
	}
	table->thread_array = init_thread_array(table);
	if (!table->thread_array)
	{
		print_error("Error initializing thread array");
		free_table(table);
		return (false);
	}
	return (true);
}

bool prepare_numbers(char **argv)
{
	if (!validate_numbers(argv))
	{
		print_error("Invalid arguments, must be numbers");
		return (false);
	}
	return (true);
}

// initialize the table
t_table	*init_table(char **argv)
{
	t_table *table;

	table = malloc(sizeof(t_table));
	if (!table)
	{
		print_error("Error allocating memory");
		return (NULL);
	}
	memset(table, 0, sizeof(t_table));
	if (!prepare_numbers(argv))
	{
		free(table);
		return (NULL);
	}
	if (!populate(table, argv))
		return (NULL);
	if (!prepare_philos(table))
		return (NULL);
	return (table);
}