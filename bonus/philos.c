/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:08:27 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/04 21:35:05 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	print_philo_info(t_philo_b *philo)
{
	printf("Philosopher nbr: %d\n", philo->id);
	printf("Eat count: %d\n", philo->eat_count);
	printf("Last eat: %ld\n", philo->last_eat);
	printf("Is dead: %d\n", philo->is_dead);
	printf("Full: %d\n", philo->full);
	printf("\n---\n");
}

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
            philo_life_sem(table->philos[i]);
            exit(0);
        }
		i++;
	}
}

void	wait_philos_b(t_table_b *table)
{
	int	i;
	int	status;

	i = 0;
	while (i < table->n_philos)
	{
		waitpid(table->philos[i]->philos_pid, &status, 0);
		i++;
	}
}
