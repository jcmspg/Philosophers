/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:45:47 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/08 23:27:21 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// function to run the simulation of the philosophers life cycle
// they will try to grab the forks, eat, release the forks and sleep
// they will repeat this until the simulation ends
// they die if they take too long to start eating.

bool	check_all_ate(t_table *table)
{
	int	i;

	i = 0;
	if (table->must_eat_count == 0)
		return (false);
	pthread_mutex_lock(&table->write);
	while (i < table->n_philos)
	{
		pthread_mutex_lock(&table->philos[i].n_eat);
		if (table->philos[i].eat_count < table->must_eat_count)
		{
			pthread_mutex_unlock(&table->philos[i].n_eat);
			pthread_mutex_unlock(&table->write);
			return (false);
		}
		pthread_mutex_unlock(&table->philos[i].n_eat);
		i++;
	}
	pthread_mutex_unlock(&table->write);
	return (true);
}

void	grab_forks(t_philo *philo)
{
	long	timestamp;

	if (philo->right_fork < 0 || philo->left_fork < 0)
		return ;
	pthread_mutex_lock(&philo->table->write);
	if (philo->table->simulating == false)
	{
		pthread_mutex_unlock(&philo->table->write);
		return ;
	}
	pthread_mutex_unlock(&philo->table->write);
	pthread_mutex_lock(&philo->is_dead_mutex);
	timestamp = get_timestamp(philo->table);
	if (timestamp - philo->last_eat > philo->table->time_to_die)
	{
		philo->is_dead = true;
		philo->table->simulating = false;
		pthread_mutex_unlock(&philo->is_dead_mutex);
		print_message(philo, "died");
		return ;
	}
	pthread_mutex_unlock(&philo->is_dead_mutex);
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->is_dead_mutex);
	philo->last_eat = timestamp;
	pthread_mutex_unlock(&philo->is_dead_mutex);
	print_message(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->n_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->n_eat);
	if (check_all_ate(philo->table) == true)
	{
		pthread_mutex_lock(&philo->n_eat);
		philo->table->all_ate = true;
		pthread_mutex_unlock(&philo->n_eat);
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		write(1, "Philosopher ate\n", 16);
		return ;
	}
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	philo->eat_count++;
}

void	philo_sleep(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->write);
	if (philo->table->simulating == false)
	{
		write(1, "simuation stopped \n", 20);
		pthread_mutex_unlock(&philo->table->write);
		return ;
	}
	pthread_mutex_unlock(&philo->table->write);
	pthread_mutex_lock(&philo->is_dead_mutex);
	timestamp = get_timestamp(philo->table);
	if (timestamp - philo->last_eat > philo->table->time_to_die)
	{
        write(1, "E AQUI\n", 9);
		philo->is_dead = true;
		philo->table->simulating = false;
		pthread_mutex_unlock(&philo->is_dead_mutex);
		print_message(philo, "died");
		return ;
	}
	pthread_mutex_unlock(&philo->is_dead_mutex);
	print_message(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->write);
	if (philo->table->simulating == false)
	{
		write(1, "simuation stopped \n", 20);
		pthread_mutex_unlock(&philo->table->write);
		return ;
	}
	pthread_mutex_unlock(&philo->table->write);

	pthread_mutex_lock(&philo->is_dead_mutex);
	timestamp = get_timestamp(philo->table);
	if (timestamp - philo->last_eat > philo->table->time_to_die)
	{
		philo->is_dead = true;
		philo->table->simulating = false;
		pthread_mutex_unlock(&philo->is_dead_mutex);
		print_message(philo, "died");
		return ;
	}
	pthread_mutex_unlock(&philo->is_dead_mutex);
	print_message(philo, "is thinking");

}

void	print_message(t_philo *philo, char *msg)
{
	if (philo->table->simulating == false)
		return ;
	pthread_mutex_lock(&philo->table->write);
	print_formatted_timestamp(get_timestamp(philo->table));
	printf("Philosopher %d %s\n", philo->id, msg);
	pthread_mutex_unlock(&philo->table->write);
}
