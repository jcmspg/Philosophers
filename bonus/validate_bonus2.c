/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:34:15 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/03 21:53:18 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

// check eat count for bonus
bool check_eat_count_b(t_table_b *table)
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
bool check_time_b(t_table_b *table)
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
bool check_philos_b(t_table_b *table)
{
    if (table->n_philos < MIN_PHILOS)
        return (false);
    if (table->n_philos > MAX_PHILOS)
        return (false);
    return (true);
}

// check values
bool check_values_b(t_table_b *table)
{
    if (!check_philos_b(table))
        return (false);
    if (!check_time_b(table))
        return (false);
    if (!check_eat_count_b(table))
        return (false);
    return (true);
}

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
