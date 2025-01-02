/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:50:17 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/02 18:58:23 by joamiran         ###   ########.fr       */
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
	if (table->time_to_die > MAX_TIME)
		return (false);
	if (table->time_to_eat > MAX_TIME)
		return (false);
	if (table->time_to_sleep > MAX_TIME)
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

// validate numbers
bool	validate_numbers(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_isnumber(argv[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

// validate arguments
bool	validate_args(int argc, char **argv)
{
	if (argc < MIN_ARGS)
		return (false);
	if (argc > MAX_ARGS)
		return (false);
	if (validate_numbers(argv) == false)
		return (false);
	return (true);
}
