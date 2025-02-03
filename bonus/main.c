/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:16:49 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/03 22:03:51 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table_b	*table;

	table = validation_initialization_b(argc, argv);
	if (!table)
		return (printf("Error: Initialization failed\n"));
    create_philos(table);
    forking_philos(table);
    table->simulating = true;
	free_table_b(table);
	return (0);
}
