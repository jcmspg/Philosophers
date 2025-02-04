/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:43:02 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/04 17:43:04 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void free_table_b(t_table_b *table)
{
    int i;

    i = 0;
    if (table->philos)
    {
        while (i < table->n_philos)
        {
            free(table->philos[i]);
            i++;
        }
        free(table->philos);
    }
    free(table);
}
