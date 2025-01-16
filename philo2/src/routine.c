/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:45:47 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/16 17:24:08 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// function to run the simulation of the philosophers life cycle
// they will try to grab the forks, eat, release the forks and sleep
// they will repeat this until the simulation ends
// they die if they take too long to start eating.

// function to check if philo is dead
bool	check_death(t_philo *philo)
{
	if (philo->table->simulating == false)
		return (false);
    pthread_mutex_lock(&philo->table->eat[philo->id]);
	if (get_timestamp(philo->table)
		- philo->last_eat > philo->table->time_to_die)
	{
        pthread_mutex_unlock(&philo->table->eat[philo->id]);
		print_message(philo, "died");
		philo->is_dead = true;
		philo->table->simulating = false;
		return (true);
	}
    pthread_mutex_unlock(&philo->table->eat[philo->id]);
	return (false);
}

bool	check_all_ate(t_table *table)
{
	int	i;

	i = 0;
	if (table->must_eat_count == 0)
		return (false);

    while (i < table->n_philos)
    {
        pthread_mutex_lock(&table->eat[i]);
        if (table->philos[i].eat_count < table->must_eat_count)
        {
            pthread_mutex_unlock(&table->eat[i]);
            return (false);
        }
        pthread_mutex_unlock(&table->eat[i]);
        i++;
    }
    table->simulating = false;
	return (true);
}

void	check_end_sim(t_table *table)
{
	int	i;

	while (table->simulating == true)
	{
		i = 0;
		if (check_all_ate(table))
            table->simulating = false;
        while (i < table->n_philos)
        {
			if (check_death(&table->philos[i]))
				table->simulating = false;
			i++;
        }
	}
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

void	eat_pray_love(t_philo *philo)
{
	if (philo->id % 2 != 0)
		philo_think(philo);
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
    pthread_mutex_lock(&philo->table->eat[philo->id]);
	philo->last_eat = get_timestamp(philo->table);
    pthread_mutex_unlock(&philo->table->eat[philo->id]);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->table->eat[philo->id]);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->eat[philo->id]);
	print_message(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	print_message(philo, "is thinking");
}

void	philo_think(t_philo *philo)
{
	print_message(philo, "is thinking");
	usleep(10);
}
