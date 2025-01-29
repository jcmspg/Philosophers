/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:27:23 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 20:49:18 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

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
