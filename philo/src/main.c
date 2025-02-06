/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:48:18 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/30 17:57:06 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_table	*table;

	table = validation_initialization(argc, argv);
	if (!table)
		return (printf("Error: Initialization failed\n"));
	start_sim(table);
	free_table(table);
	return (0);
}
