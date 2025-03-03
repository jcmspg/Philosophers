/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:30:50 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/18 21:18:49 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sleeperino(t_philo *philo)
{
	if (check_bool(&philo->table->table, &philo->table->simulating) == false)
		return ;
	if (philo->table->n_philos == 1)
		return ;
	print_message(philo, "is sleeping");
	standby(philo, philo->table->time_to_sleep);
}

void	grab_forks(t_philo *philo)
{
	if (check_bool(&philo->table->table, &philo->table->simulating) == false)
		return ;
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
	if (check_if_dead(philo))
		return (pthread_mutex_unlock(&philo->table->forks[philo->right_fork]),
			(void)0);
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_message(philo, "has taken a fork");
	if (check_if_dead(philo))
		return (release_forks(philo));
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
}

void	think(t_philo *philo)
{
	if (check_bool(&philo->table->table, &philo->table->simulating) == false)
		return ;
	if (philo->table->n_philos == 1)
		return ;
	print_message(philo, "is thinking");
	if (philo->table->n_philos % 2 == 0)
		return ;
	usleep((philo->table->time_to_think) * 1000);
}

void	eat(t_philo *philo)
{
	if (check_bool(&philo->table->table, &philo->table->simulating) == false)
		return ;
	grab_forks(philo);
	if (philo->table->n_philos == 1)
		return ;
	print_message(philo, "is eating");
	handle_long(&philo->table->table, &philo->last_eat,
		get_timestamp(philo->table));
	standby(philo, philo->table->time_to_eat);
	handle_int(&philo->table->philo_mutex, &philo->eat_count, philo->eat_count
		+ 1);
	if (check_if_dead(philo))
		return (release_forks(philo));
	if (philo->table->must_eat_count > 0
		&& philo->eat_count == philo->table->must_eat_count)
		handle_bool(&philo->table->table, &philo->full, true);
	release_forks(philo);
	if (check_if_dead(philo))
		return ;
}
// place at the start of eat .. to check if the philo has more than the others
