/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:52:50 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/08 23:27:27 by joamiran         ###   ########.fr       */
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
	printf("Last eat: %d\n", philo->last_eat);
	printf("Right fork: %d\n", philo->right_fork);
	printf("Left fork: %d\n", philo->left_fork);
	printf("\n---\n");
}

// print ALL the philos
void	print_all_info(t_table *table)
{
	int	i;

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
