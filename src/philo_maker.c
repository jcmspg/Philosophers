/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:46:11 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/27 20:38:04 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	assing_forks(t_table *table, int id)
{
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
}

void	init_philo(t_table *table, int id)
{
	table->philos[id].id = id;
	table->philos[id].eat_count = 0;
	table->philos[id].last_eat = 0;
	table->philos[id].is_dead = false;
	table->philos[id].full = false;
	assing_forks(table, id);
	table->philos[id].table = table;
}

t_philo	*autobots_assemble(t_table *table)
{
	int	i;

	i = 0;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->n_philos);
	if (!table->philos)
	{
		print_error("Error creating philosophers");
		return (NULL);
	}
	while (i < table->n_philos)
	{
		init_philo(table, i);
		i++;
	}
	return (table->philos);
}
