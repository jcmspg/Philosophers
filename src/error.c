/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:52:50 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 16:20:51 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// print error message
int	print_error(char *msg)
{
	return (printf("Error: %s\n", msg));
}

// print table info
void	print_table_info(t_table *table)
{
	printf("Table info:\n");
	printf("Number of philosophers: %d\n", table->n_philos);
	printf("Time to die: %ldms\n", table->time_to_die / 1000);
	printf("Time to eat: %ldms\n", table->time_to_eat / 1000);
	printf("Time to sleep: %ldms\n", table->time_to_sleep / 1000);
	printf("Number of times each philosopher must eat: %d\n",
		table->must_eat_count);
	printf("Number of forks: %d\n", table->n_forks);
	printf("Simulation status: %d\n", table->simulating);
	printf("Ready set go: %d\n", table->ready_set_go);
	printf("All ate: %d\n", table->all_ate);
	printf("Start time: %ld\n", table->start_time.tv_usec);
	printf("\n");
}

// print each philo's forks
void	print_forks(t_philo *philo)
{
	printf("Philosopher nbr: %d\n", philo->id);
	printf("Right fork: %d\n", philo->right_fork);
	printf("Left fork: %d\n", philo->left_fork);
	printf("\n---\n");
}

// print philo info
void	print_info(t_philo *philo)
{
	printf("Philosopher nbr: %d\n", philo->id);
	printf("Eat count: %d\n", philo->eat_count);
	printf("Last eat: %ld\n", philo->last_eat);
	printf("Is dead: %d\n", philo->is_dead);
	printf("Full: %d\n", philo->full);
	print_forks(philo);
	printf("\n---\n");
}

// print ALL the philos
void	print_all_info(t_table *table)
{
	int	i;

	print_table_info(table);
	i = 0;
	while (i < table->n_philos)
	{
		print_info(&table->philos[i]);
		i++;
	}
}
