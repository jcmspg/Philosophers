/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:27:23 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/03 21:46:51 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void init_semaphores(t_table_b *table)
{
    table->sem_forks = sem_open(SEM_FORK_NAME, O_CREAT, 0644, table->n_philos);
    table->sem_print = sem_open("/sem_print", O_CREAT, 0644, 1);
    if (table->sem_forks == SEM_FAILED || table->sem_print == SEM_FAILED)
    {
        print_error("Error: Semaphore failed");
        exit(1);
    }
}


t_table_b *validation_initialization_b(int argc, char **argv)
{
    t_table_b   *table;

    if (validate_args(argc, argv) == false)
    {
        print_error("Error: Invalid arguments");
        return (NULL);
    }
    table = init_table_b(argv);
    if (!table)
    {
        print_error("Error: Table initialization failed");
        return (NULL);
    }
    init_semaphores(table);
    return (table);
}
