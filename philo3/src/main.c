/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:48:18 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/16 17:39:49 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	free_table(table);
	return (0);
}
