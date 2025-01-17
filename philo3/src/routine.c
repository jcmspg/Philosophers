/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:45:47 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/17 18:04:24 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// function to run the simulation of the philosophers life cycle
// they will try to grab the forks, eat, release the forks and sleep
// they will repeat this until the simulation ends
// they die if they take too long to eat.

// grab the forks
void	grab_forks(t_philo *philo)
{
	if (check_death(philo->table, philo))
	{
		pthread_mutex_lock(&philo->table->control);
		philo->table->simulating = false;
		pthread_mutex_unlock(&philo->table->control);
		return ;
	}
	if (check_all_ate(philo->table))
	{
		pthread_mutex_lock(&philo->table->control);
		philo->table->simulating = false;
		pthread_mutex_unlock(&philo->table->control);
		return ;
	}

    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
        print_message(philo, "has taken a fork");
        pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
        print_message(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
        print_message(philo, "has taken a fork");
        pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
        print_message(philo, "has taken a fork");
    }
}

// release the forks
void	release_forks(t_philo *philo)
{
	if (check_death(philo->table, philo))
	{
		pthread_mutex_lock(&philo->table->control);
		philo->table->simulating = false;
		pthread_mutex_unlock(&philo->table->control);
		return ;
	}
	if (check_all_ate(philo->table))
	{
		pthread_mutex_lock(&philo->table->control);
		philo->table->simulating = false;
		pthread_mutex_unlock(&philo->table->control);
		return ;
	}
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
}

// eat
void	eat(t_philo *philo)
{
	if (check_death(philo->table, philo))
	{
		pthread_mutex_lock(&philo->table->control);
		philo->table->simulating = false;
		pthread_mutex_unlock(&philo->table->control);
		return ;
	}
	if (check_all_ate(philo->table))
	{
		pthread_mutex_lock(&philo->table->control);
		philo->table->simulating = false;
		pthread_mutex_unlock(&philo->table->control);
		return ;
	}
	print_message(philo, "is eating");
	philo->last_eat = get_timestamp(philo->table);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->table->n_eat[philo->id]);
	philo->eat_count++;
	philo->table->eat_count[philo->id]++;
}

void sleep_philo(t_philo *philo)
{
    if (check_death(philo->table, philo))
    {
        pthread_mutex_lock(&philo->table->control);
        philo->table->simulating = false;
        pthread_mutex_unlock(&philo->table->control);
        return ;
    }
    if (check_all_ate(philo->table))
    {
        pthread_mutex_lock(&philo->table->control);
        philo->table->simulating = false;
        pthread_mutex_unlock(&philo->table->control);
        return ;
    }
    print_message(philo, "is sleeping");
    usleep(philo->table->time_to_sleep * 1000);
}

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->control);
	if (philo->table->simulating == false)
	{
		pthread_mutex_unlock(&philo->table->control);
		return ;
	}
	pthread_mutex_unlock(&philo->table->control);
	pthread_mutex_lock(&philo->table->write);
	print_formatted_timestamp(get_timestamp(philo->table));
	printf("Philosopher %d %s\n", philo->id, msg);
	pthread_mutex_unlock(&philo->table->write);
}
