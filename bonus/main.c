/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:16:49 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 21:20:36 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int main(int argc, char **argv) {
  t_table_b *table;

  table = validation_initialization_b(argc, argv);
  if (!table)
    return (printf("Error: Initialization failed\n"));

  if (!start_simulation(table))
  {
    cleanup_semaphore(table);
    free_table_b(table);
    return (printf("Error: Simulation failed\n"));
  }

  while (table->simulating)
  {
    rotate_eating_group(table, table->round);
    table->round++;
  }
  cleanup_semaphore(table);
  free_table_b(table);
  return (0);
}
