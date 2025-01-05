/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:19:00 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/03 20:11:06 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_table	*init_table(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	if (!validate_numbers(argv))
	{
		free(table);
		return (NULL);
	}
	assign_values(table, argv);
	if (!check_philos(table) || !check_time(table) || !check_eat_count(table))
	{
		free(table);
		return (NULL);
	}

    ft_start_time(table);

	return (table);
}

void	free_table(t_table *table)
{
	if (!table)
		return ;
    if (table->philos)
	    free_philos(table);
    if (table->thread_array)
        free_thread_array(table);
    if (table->forks)
        free_forks(table);
    if (table)
        free(table);
}
