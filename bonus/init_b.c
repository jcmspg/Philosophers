/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:51:12 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 21:30:54 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

// assign values for bonus
bool	populate_b(t_table_b *table, char **argv)
{
	assign_values_b(table, argv);
	if (!check_values_b(table))
	{
		free(table);
		print_error("Error: Invalid values");
		return (false);
	}
	table->simulating = false;
	table->all_ate = false;
	table->semaphore = NULL;
	return (true);
}

// init checker for bonus
static bool	check_init_b(t_table_b *table, char **argv)
{
	if (!table)
		return (false);
	if (!prepare_numbers(argv))
	{
		if (table)
			free(table);
		return (false);
	}
	if (!populate_b(table, argv))
	{
		if (table)
			free(table);
		return (false);
	}
	return (true);
}

// initialize table for bonus
t_table_b	*init_table_b(char **argv)
{
	t_table_b	*table;

	table = (t_table_b *)malloc(sizeof(t_table_b));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table_b));
	if (!check_init_b(table, argv))
		return (NULL);
	return (table);
}
