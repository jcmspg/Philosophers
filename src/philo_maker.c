/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:46:11 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/03 20:43:04 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    free_philos(t_table *table)
{
    if (!table->philos)
        return ;
    free(table->philos);
}

void	init_philo(t_table *table, int id)
{
    table->philos[id].id = id + 1;
    table->philos[id].eat_count = 0;
    table->philos[id].last_eat = 0;
    table->philos[id].right_fork = 0;
    table->philos[id].left_fork = 0;
}

t_philo	*autobots_assemble(t_table *table)
{
    int i;

    i = 0;
    table->philos = malloc(sizeof(t_philo) * (table->n_philos));
    if (!table->philos)
        return (NULL);
    memset(table->philos, 0, sizeof(t_philo) * (table->n_philos));
    while (i < table->n_philos)
    {
        init_philo(table, i);
        i++;
    }
    return (table->philos);
}

