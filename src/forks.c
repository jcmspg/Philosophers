/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:28:34 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/22 17:26:10 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"



// create the fork array
void init_forks(t_table *table)
{
    table->forks = malloc(sizeof(pthread_mutex_t) * table->n_forks);
    if (!table->forks)
    {
        print_error("Malloc failed");
        return ;
    }
    memset(table->forks, 0, sizeof(pthread_mutex_t) * table->n_forks);
    return ;
}
