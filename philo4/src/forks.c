/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:28:34 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/17 21:55:34 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// free the forks
void	free_forks(t_table *table)
{
    int	i;

    i = 0;
    while (i < table->n_forks)
    {
        if (pthread_mutex_destroy(&table->forks[i]))
        {
            print_error("Mutex destroy failed");
            return ;
        }
        i++;
    }
    free(table->forks);
}

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
