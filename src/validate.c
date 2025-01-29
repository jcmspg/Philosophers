/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:50:17 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 21:20:03 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// check eat count
bool	check_eat_count(t_table *table)
{
	if (table->must_eat_count < MIN_EAT_COUNT)
		return (false);
	if (table->must_eat_count > MAX_EAT_COUNT)
		return (false);
	if (table->must_eat_count == 0)
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
		return (false);
	if (!check_time(table))
		return (false);
	if (!check_eat_count(table))
	    return (false);
	return (true);
}
