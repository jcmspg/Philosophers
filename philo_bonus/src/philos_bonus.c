/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:08:27 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/06 18:03:26 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

/*static void	print_philo_info(t_philo_b *philo)
{
	printf("Philosopher nbr: %d\n", philo->id);
	printf("Eat count: %d\n", philo->eat_count);
	printf("Last eat: %ld\n", philo->last_eat);
	printf("Is dead: %d\n", philo->is_dead);
	printf("Full: %d\n", philo->full);
	printf("\n---\n");
}*/

t_philo_b	*create_philo_b(t_table_b *table, int id)
{
	t_philo_b	*philo;

	philo = (t_philo_b *)malloc(sizeof(t_philo_b));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo_b));
	philo->id = id + 1;
	philo->table = table;
	philo->eat_count = 0;
	philo->last_eat = 0;
	philo->full = false;
	philo->is_dead = false;
	philo->philos_pid = 0;
	return (philo);
}

void	create_philos_b(t_table_b *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i] = create_philo_b(table, i);
		if (!table->philos[i])
		{
			free(table->philos);
			return ;
		}
		i++;
	}
}

void	forking_philos_b(t_table_b *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i]->philos_pid = fork();
		if (table->philos[i]->philos_pid == 0)
		{
			table->philos[i]->last_eat = get_timestamp_b(table);
			monitor(table->philos[i]);
		}
		else if (table->philos[i]->philos_pid < 0)
		{
			print_error_b("Error: Fork failed");
			exit(1);
		}
		usleep(100);
		i++;
	}
}
