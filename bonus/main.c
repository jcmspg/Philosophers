/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:16:49 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/05 18:47:25 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table_b	*table;

	table = validation_initialization_b(argc, argv);
	if (!table)
		return (printf("Error: Initialization failed\n"));
    create_philos_b(table);
    ft_start_time_b(table);
    forking_philos_b(table);
    wrap_up(table);
	free_table_b(table);
	return (0);
}
