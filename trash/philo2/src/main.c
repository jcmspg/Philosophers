/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:48:18 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/15 16:07:43 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static t_table	*validation_initialization(int argc, char **argv)
{
	t_table	*table;

	if (validate_args(argc, argv) == false)
		return (NULL);
	table = init_table(argv);
	if (!table)
		return (NULL);
	if (autobots_assemble(table) == NULL)
	{
		free_table(table);
		return (NULL);
	}
	init_forks(table);
	if (!table->forks)
	{
		free_table(table);
		return (NULL);
	}
    init_eatcount(table);
    if (!table->eat)
    {
        free_table(table);
        return (NULL);
    }
	return (table);
}

static bool	check_thread_array(t_table *table)
{
	table->thread_array = create_thread_array(table);
	if (!table->thread_array)
	{
		print_error("Error creating thread array");
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = validation_initialization(argc, argv);
	if (!table)
		return (printf("Error: Initialization failed\n"));
	if (!check_thread_array(table))
	{
		free_table(table);
		return (printf("Error: Thread array failed\n"));
	}
	start_sim(table);
    destroy_mutexes(table);
	free_table(table);
	return (0);
}
