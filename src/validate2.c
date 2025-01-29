/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:52:21 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 16:56:42 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

// validation initialization
t_table	*validation_initialization(int argc, char **argv)
{
	t_table	*table;

	if (validate_args(argc, argv) == false)
	{
		print_error("Invalid arguments");
		return (NULL);
	}
	table = init_table(argv);
	if (!table)
	{
		print_error("Error initializing table");
		return (NULL);
	}
	init_table_mutexes(table);
	return (table);
}
