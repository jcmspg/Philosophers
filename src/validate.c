/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:50:17 by joamiran          #+#    #+#             */
/*   Updated: 2024/12/30 18:56:03 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// validate arguments
bool validate_args(int argc, char **argv, t_table *table)
{
    if (argc < 5 || argc > 6)
        return (false);
    table->n_philos = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        table->must_eat_count = ft_atoi(argv[5]);
    else
        table->must_eat_count = -1;
    return (true);
}
