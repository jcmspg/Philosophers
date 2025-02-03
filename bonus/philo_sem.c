/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:44:27 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/03 22:06:14 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

// function to print philosopher's actions safely
void	print_sem(t_philo_b *philo, char *msg)
{
	sem_wait(philo->table->sem_print);
	print_message_b(philo, msg);
	sem_post(philo->table->sem_print);
}

// function to think
void	think_sem(t_philo_b *philo)
{
	print_sem(philo, "is thinking");
}

// function to check the death of the philosopher
bool	check_death_sem(t_philo_b *philo)
{
	long	current_time;

	current_time = get_timestamp_b(philo->table);
	if (current_time - philo->last_eat >= philo->table->time_to_die)
	{
		// if holding the forks, release them
		if (philo->right_fork)
			sem_post(philo->right_fork);
		if (philo->left_fork)
			sem_post(philo->left_fork);
		print_sem(philo, "died");
		return (true);
	}
	return (false);
}

// function to check if the philosopher is dead
bool	check_end(t_philo_b *philo)
{
	if (philo->full)
		return (true);
	if (check_death_sem(philo))
		return (true);
	return (false);
}

// function to eat
void	eat_sem(t_philo_b *philo)
{
	sem_wait(philo->left_fork);
	print_sem(philo, "has taken left fork");
	sem_wait(philo->right_fork);
	print_sem(philo, "has taken right fork");
	print_sem(philo, "is eating");
	philo->last_eat = get_timestamp_b(philo->table);
	usleep(philo->table->time_to_eat * 1000);
	sem_post(philo->right_fork);
	sem_post(philo->left_fork);
	if (philo->table->must_eat_count > 0)
	{
		philo->eat_count++;
		if (philo->eat_count >= philo->table->must_eat_count)
			philo->full = true;
	}
}

// function to sleep
void	sleep_sem(t_philo_b *philo)
{
	print_sem(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

// function to run the philosopher's life cycle
void	philo_life_sem(t_philo_b *philo)
{
	while (philo->table->simulating)
	{
		while (!check_end(philo))
		{
			think_sem(philo);
			eat_sem(philo);
			sleep_sem(philo);
		}
	}
}
