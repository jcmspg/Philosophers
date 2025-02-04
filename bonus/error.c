/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:52:50 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/04 17:38:45 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

// print error message
int	print_error_b(char *msg)
{
	return (printf("Error: %s\n", msg));
}

// print table info
void	print_table_info_b(t_table_b *table)
{
	printf("Table info:\n");
	printf("Number of philosophers: %d\n", table->n_philos);
	printf("Time to die: %ldms\n", table->time_to_die);
	printf("Time to eat: %ldms\n", table->time_to_eat);
	printf("Time to sleep: %ldms\n", table->time_to_sleep);
	printf("Number of times each philosopher must eat: %d\n",
		table->must_eat_count);
	printf("Number of forks: %d\n", table->n_philos);
	printf("Simulation status: %d\n", table->simulating);
	printf("All ate: %d\n", table->all_ate);
	printf("Start time: %ld\n", table->start_time.tv_usec);
	printf("\n");
}

// print philo info
void	print_info_b(t_philo_b *philo)
{
	printf("Philosopher nbr: %d\n", philo->id);
	printf("Eat count: %d\n", philo->eat_count);
	printf("Last eat: %ld\n", philo->last_eat);
	printf("Is dead: %d\n", philo->is_dead);
	printf("Full: %d\n", philo->full);
	printf("\n---\n");
}

// print ALL the philos
void	print_all_info_b(t_table_b *table)
{
	int	i;

	print_table_info_b(table);
	i = 0;
	while (i < table->n_philos)
	{
		print_info_b(table->philos[i]);
		i++;
	}
}

void	print_results_b(t_table_b *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		printf("Philosopher %d ate %d times\n", table->philos[i]->id,
			table->philos[i]->eat_count);
		i++;
	}
}
