/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:24:28 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 21:33:19 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"
#include <semaphore.h>

void init_semaphore(t_table_b *table)
{
    table->semaphore = sem_open("semaphore", O_CREAT, 0644, table->group_size);
    if (table->semaphore == SEM_FAILED)
        {
            printf("Error: semaphore failed\n");
            exit(1);
        }
}

void cleanup_semaphore(t_table_b *table)
{
    sem_close(table->semaphore);
    sem_unlink("semaphore");
}
