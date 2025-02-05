/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 21:07:58 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/05 02:39:49 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void print_philo(t_philo_b *philo, char *msg)
{
    pthread_mutex_lock(&philo->table->print);
    if (!philo->table->simulating)
    {
        long time;

        time = get_timestamp_b(philo->table);
        print_formatted_timestamp_b(time);
        printf("%d %s\n", philo->id, msg);
    }
    pthread_mutex_unlock(&philo->table->print);
}