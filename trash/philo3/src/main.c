/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:48:18 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/17 16:30:11 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = validation_initialization(argc, argv);
	if (!table)
		return (printf("Error: Initialization failed\n"));

    //print the table info
 //   printf("Table info:\n");
 //   printf("Number of philosophers: %d\n", table->n_philos);
 //   printf("Time to die: %d\n", table->time_to_die);
 //   printf("Time to eat: %d\n", table->time_to_eat);
 //   printf("Time to sleep: %d\n", table->time_to_sleep);
 //   printf("Number of times each philosopher must eat: %d\n", table->must_eat_count);
 //   printf("Number of forks: %d\n", table->n_forks);
 //   printf("\n");




	if (!check_thread_array(table))
	{
		free_table(table);
		return (printf("Error: Thread array failed\n"));
	}
	start_sim(table);
	free_table(table);
	return (0);
}
