/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:07:58 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/03 21:49:18 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include "../philo_bonus.h"

// assign values for bonus
void assign_values_b(t_table_b *table, char **argv)
{
    int i;

    i = 0;
    table->n_philos = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
    {
        i = ft_atoi(argv[5]);
        if (i < 0)
            table->must_eat_count = -2;
        else
            table->must_eat_count = i;
    }
    else
        table->must_eat_count = -1;
}
