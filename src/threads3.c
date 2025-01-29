/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:30:50 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 16:31:15 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sleeperino(t_philo *philo)
{
	print_message(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void	grab_forks(t_philo *philo)
{
	if (philo->table->n_philos == 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_message(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		usleep(philo->table->time_to_die * 1000);
		return ;
	}
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_message(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
}

void	think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	eat(t_philo *philo)
{
	if (has_lower_eat_count(philo))
		usleep(100);
	if (!check_all_ate(philo))
		usleep(100);
	grab_forks(philo);
	if (philo->table->n_philos == 1)
	{
		return ;
	}
	print_message(philo, "is eating");
	handle_long(&philo->table->table, &philo->last_eat,
		get_timestamp(philo->table));
	handle_int(&philo->table->table, &philo->eat_count, philo->eat_count + 1);
	usleep(philo->table->time_to_eat * 1000);
	if (check_if_dead(philo))
	{
		release_forks(philo);
		return ;
	}
	if (philo->table->must_eat_count > 0
		&& philo->eat_count == philo->table->must_eat_count)
		handle_bool(&philo->table->table, &philo->full, true);
	release_forks(philo);
	if (check_if_dead(philo))
		return ;
}
