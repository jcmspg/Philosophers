/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:52:50 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/17 21:18:20 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// print error message
int	print_error(char *msg)
{
	return (printf("Error: %s\n", msg));
}

// print philo info
void	print_info(t_philo *philo)
{
	printf("Philosopher nbr: %d\n", philo->id);
	printf("Eat count: %d\n", philo->eat_count);
	printf("Last eat: %ld\n", philo->last_eat);
	printf("Is dead: %d\n", philo->is_dead);
	printf("Full: %d\n", philo->full);
	printf("Right fork: %d\n", philo->right_fork);
	printf("Left fork: %d\n", philo->left_fork);
	printf("\n---\n");
}

// print table info
void	print_table_info(t_table *table)
{
	printf("Table info:\n");
	printf("Number of philosophers: %d\n", table->n_philos);
	printf("Time to die: %d\n", table->time_to_die);
	printf("Time to eat: %d\n", table->time_to_eat);
	printf("Time to sleep: %d\n", table->time_to_sleep);
	printf("Number of times each philosopher must eat: %d\n",
		table->must_eat_count);
	printf("Number of forks: %d\n", table->n_forks);
	printf("\n");
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

// print each philo's forks
void	print_forks(t_philo *philo)
{
	printf("Philosopher nbr: %d\n", philo->id);
	printf("Right fork: %d\n", philo->right_fork);
	printf("Left fork: %d\n", philo->left_fork);
	printf("\n---\n");
}
