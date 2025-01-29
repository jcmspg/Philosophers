/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:50:17 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 16:52:44 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// check thread array
bool	check_thread_array(t_table *table)
{
	table->thread_array = init_thread_array(table);
	if (!table->thread_array)
	{
		print_error("Error creating thread array");
		return (false);
	}
	return (true);
}

// check eat count
bool	check_eat_count(t_table *table)
{
	if (table->must_eat_count < MIN_EAT_COUNT)
		return (false);
	if (table->must_eat_count > MAX_EAT_COUNT)
		return (false);
	return (true);
}

// check time
bool	check_time(t_table *table)
{
	if (table->time_to_die < MIN_TIME)
		return (false);
	if (table->time_to_eat < MIN_TIME)
		return (false);
	if (table->time_to_sleep < MIN_TIME)
		return (false);
	if ((table->time_to_die) > MAX_TIME)
		return (false);
	if ((table->time_to_eat) > MAX_TIME)
		return (false);
	if ((table->time_to_sleep) > MAX_TIME)
		return (false);
	return (true);
}

// check philos
bool	check_philos(t_table *table)
{
	if (table->n_philos < MIN_PHILOS)
		return (false);
	if (table->n_philos > MAX_PHILOS)
		return (false);
	return (true);
}

bool	check_values(t_table *table)
{
	if (!check_philos(table))
	{
		print_error("Invalid number of philosophers");
		return (false);
	}
	if (!check_time(table))
	{
		print_error("Invalid time values");
		return (false);
	}
	if (!check_eat_count(table))
	{
		print_error("Invalid number of times each philosopher must eat");
		return (false);
	}
	return (true);
}
