/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:45:47 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/06 21:32:17 by joamiran         ###   ########.fr       */
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

    if((pthread_mutex_lock(&philo->table->forks[philo->right_fork])) != 0)
        pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    printf("Philosopher %d has taken a fork\n", philo->id);
    printf("Philosopher %d has taken a fork\n", philo->id);

}

void	philo_sleep(t_philo *philo)
{
	print_formatted_timestamp(get_timestamp(philo->table));
	printf("Philosopher %d is sleeping\n", philo->id);
	usleep(philo->table->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	print_formatted_timestamp(get_timestamp(philo->table));
	printf("Philosopher %d is thinking\n", philo->id);
	usleep(1000);
}

void	philo_eat(t_philo *philo)
{
	print_formatted_timestamp(get_timestamp(philo->table));
	printf("Philosopher %d is eating\n", philo->id);
	philo->last_eat = get_timestamp(philo->table);
	usleep(philo->table->time_to_eat * 1000);
	philo->eat_count++;
}
