/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:27:23 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/06 17:42:06 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

// validate arguments
bool	validate_args(int argc, char **argv)
{
	if (argc < MIN_ARGS)
		return (false);
	if (argc > MAX_ARGS)
		return (false);
	if (validate_numbers(argv) == false)
		return (false);
	return (true);
}

void	init_semaphores(t_table_b *table)
{
	sem_unlink(SEM_FORK_R_NAME);
	sem_unlink(SEM_FORK_L_NAME);
	sem_unlink(SEM_PRINT_NAME);
	sem_unlink(SEM_EXTRA_NAME);
	table->extra = sem_open(SEM_EXTRA_NAME, O_CREAT, 0644, 1);
	table->right_fork = sem_open(SEM_FORK_R_NAME, O_CREAT, 0644, table->n_philos
			/ 2);
	table->left_fork = sem_open(SEM_FORK_L_NAME, O_CREAT, 0644, table->n_philos
			/ 2);
	table->sem_print = sem_open(SEM_PRINT_NAME, O_CREAT, 0644, 1);
	if (table->sem_print == SEM_FAILED || table->right_fork == SEM_FAILED
		|| table->left_fork == SEM_FAILED)
	{
		print_error_b("Error: Semaphore failed");
		exit(1);
	}
}

t_table_b	*validation_initialization_b(int argc, char **argv)
{
	t_table_b	*table;

	if (validate_args(argc, argv) == false)
	{
		print_error_b("Error: Invalid arguments");
		return (NULL);
	}
	table = init_table_b(argv);
	if (!table)
	{
		print_error_b("Error: Table initialization failed");
		return (NULL);
	}
	pthread_mutex_init(&table->print, NULL);
	init_semaphores(table);
	return (table);
}
