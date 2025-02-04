/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:44:27 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/04 21:36:37 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

// function to print philosopher's actions safely
void	print_sem(t_philo_b *philo, char *msg)
{
	print_message_b(philo, msg);
}

// function to think
void	think_sem(t_philo_b *philo)
{
    printf("%ld %d is thinking\n", get_timestamp_b(philo->table), philo->id);
}

// function to check the death of the philosopher
bool	check_death_sem(t_philo_b *philo)
{
	long	current_time;
    
    current_time = get_timestamp_b(philo->table);
    if (current_time - philo->last_eat > philo->table->time_to_die)
    {
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
//	sem_wait(philo->table->right_fork);
//    sem_wait(philo->table->left_fork);
    printf("%ld %d has taken left fork\n", get_timestamp_b(philo->table), philo->id);
    printf("%ld %d has taken right fork\n", get_timestamp_b(philo->table), philo->id);
	philo->last_eat = get_timestamp_b(philo->table);
    printf("%ld %d is eating\n", get_timestamp_b(philo->table), philo->id);
	usleep(philo->table->time_to_eat * 1000);
//	sem_post(philo->table->right_fork);
//	sem_post(philo->table->left_fork);
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
    printf("%ld %d is sleeping\n", get_timestamp_b(philo->table), philo->id);
	usleep(philo->table->time_to_sleep * 1000);
}

// function to run the philosopher's life cycle
void	philo_life_sem(t_philo_b *philo)
{
	while (!philo->full)
	{
        if (philo->id % 2 != 0)
            usleep(100);
        sem_wait(philo->table->right_fork);
        eat_sem(philo);
        sem_post(philo->table->right_fork);
        sleep_sem(philo);
		think_sem(philo);
	}
}
