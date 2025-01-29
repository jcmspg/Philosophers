/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_maker_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:21:24 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 21:28:26 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void assign_forks_b(t_table_b *table, int id)
{
    table->philos[id].left_fork = id;
    table->philos[id].right_fork = (id + 1) % table->n_philos;
}

void init_philo_b(t_table_b *table, int id)
{
    table->philos[id].id = id;
    table->philos[id].eat_count = 0;
    table->philos[id].last_eat = 0;
    table->philos[id].is_dead = false;
    table->philos[id].full = false;
    assign_forks_b(table, id);
    table->philos[id].table = table;
}

t_philo_b *autobots_assemble_b(t_table_b *table)
{
    int i;

    i = 0;
    table->philos = (t_philo_b *)malloc(sizeof(t_philo_b) * table->n_philos);
    if (!table->philos)
        return (NULL);
    while (i < table->n_philos)
    {
        init_philo_b(table, i);
        i++;
    }
    return (table->philos);
}

