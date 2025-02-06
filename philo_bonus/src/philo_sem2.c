/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:44:00 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/06 17:47:22 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	clean_house(t_table_b *table)
{
	sem_close(table->extra);
	sem_close(table->right_fork);
	sem_close(table->left_fork);
	sem_close(table->sem_print);
	sem_unlink(SEM_EXTRA_NAME);
	sem_unlink(SEM_FORK_R_NAME);
	sem_unlink(SEM_FORK_L_NAME);
	sem_unlink(SEM_PRINT_NAME);
}

void	live_and_let_die(t_philo_b *philo)
{
	sem_wait(philo->table->right_fork);
	print_philo(philo, "has taken a fork");
	sem_wait(philo->table->left_fork);
	print_philo(philo, "has taken a fork");
	print_philo(philo, "is eating");
	philo->last_eat = get_timestamp_b(philo->table);
	usleep(philo->table->time_to_eat * 1000);
	sem_post(philo->table->right_fork);
	sem_post(philo->table->left_fork);
	philo->eat_count++;
	print_philo(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	print_philo(philo, "is thinking");
}
