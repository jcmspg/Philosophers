/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:45:47 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/07 20:34:38 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// function to run the simulation of the philosophers life cycle
// they will try to grab the forks, eat, release the forks and sleep
// they will repeat this until the simulation ends
// they die if they take too long to eat.

void	grab_forks(t_philo *philo)
{
	if (philo->right_fork < 0 || philo->left_fork < 0)
		return ;

    pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
    print_message(philo, "has taken a fork");
    pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    print_message(philo, "has taken a fork");
   
    print_message(philo, "is eating");
	philo->last_eat = get_timestamp(philo->table);
	usleep(philo->table->time_to_eat * 1000);
    
    pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
    pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
   
    pthread_mutex_lock(&philo->table->control);
    pthread_mutex_lock(&philo->n_eat);
    philo->eat_count++;
    pthread_mutex_unlock(&philo->n_eat);
    pthread_mutex_unlock(&philo->table->control);
}

void	philo_sleep(t_philo *philo)
{
    print_message(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
    print_message(philo, "is thinking");
    if (philo->table->n_philos % 2 != 0)
        usleep(100);
}

void    print_message(t_philo *philo, char *msg)
{
    pthread_mutex_lock(&philo->table->write);
    print_formatted_timestamp(get_timestamp(philo->table));
    printf("Philosopher %d %s\n", philo->id, msg);
    pthread_mutex_unlock(&philo->table->write);
}
