/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:46:11 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/06 18:58:03 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_philos(t_table *table)
{
	if (!table->philos)
		return ;
	free(table->philos);
}

void	init_philo(t_table *table, int id)
{
	table->philos[id].id = id;
	table->philos[id].eat_count = 0;
	table->philos[id].last_eat = 0;
	if (id % 2 == 0)
	{
		table->philos[id].right_fork = id;
		table->philos[id].left_fork = (id + 1) % table->n_philos;
	}
	else
	{
		table->philos[id].right_fork = (id + 1) % table->n_philos;
		table->philos[id].left_fork = id;
	}
	table->philos[id].table = table;
}

t_philo	*autobots_assemble(t_table *table)
{
	int	i;

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
