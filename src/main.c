/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:48:18 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/03 20:43:55 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	if (validate_args(argc, argv) == false)
		return (printf("Invalid Arguments.\nExample: ./philo 5 800 200 200\n"));
	
    table = init_table(argv);
	if (!table)
		return (printf("Error: Invalid arguments\n"));
    
    if (!autobots_assemble(table))
    {
        free_table(table);
        return (printf("Error: Memory allocation failed\n"));
    }

    print_all_info(table);
    
    table->thread_array = create_thread_array(table);
	
    start_sim(table);
	free_table(table);
	return (0);
}
