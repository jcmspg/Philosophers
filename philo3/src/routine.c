/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:45:47 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/16 19:37:19 by joamiran         ###   ########.fr       */
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
    if(check_death(philo->table, philo))
    {
        pthread_mutex_lock(&philo->table->control);
        philo->table->simulating = false;
        pthread_mutex_unlock(&philo->table->control);
        return ;
    }
    pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
    print_message(philo, "has taken a fork");
    pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    print_message(philo, "has taken a fork");
}

// release the forks
void	release_forks(t_philo *philo)
{
    if(check_death(philo->table, philo))
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
    if(check_death(philo->table, philo))
    {
        pthread_mutex_lock(&philo->table->control);
        philo->table->simulating = false;
        pthread_mutex_unlock(&philo->table->control);
        return ;
    }
    print_message(philo, "is eating");
    philo->last_eat = get_timestamp(philo->table);
    usleep(philo->table->time_to_eat * 1000);
    pthread_mutex_lock(&philo->n_eat);
    philo->eat_count++;
    pthread_mutex_unlock(&philo->n_eat);
}

// sleep
void	sleep_philo(t_philo *philo)
{
    if(check_death(philo->table, philo))
    {
        pthread_mutex_lock(&philo->table->control);
        philo->table->simulating = false;
        pthread_mutex_unlock(&philo->table->control);
        return ;
    }
    print_message(philo, "is sleeping");
    usleep(philo->table->time_to_sleep * 1000);
}

// philo think
void	think(t_philo *philo)
{
    if(check_death(philo->table, philo))
    {
        pthread_mutex_lock(&philo->table->control);
        philo->table->simulating = false;
        pthread_mutex_unlock(&philo->table->control);
        return ;
    }
    print_message(philo, "is thinking");
    usleep(100);
}

// routine to execute by each thread
void	*philo_life(void *arg)
{
    t_philo	*philo;

    philo = (t_philo *)arg;
    while (philo->table->simulating)
    {
        if (check_all_ate(philo->table))
        {
            pthread_mutex_lock(&philo->table->control);
            philo->table->simulating = false;
            pthread_mutex_unlock(&philo->table->control);
            return (NULL);
        }
        if (philo->id % 2 == 0)
            think(philo);
        grab_forks(philo);
        eat(philo);
        release_forks(philo);
        sleep_philo(philo);
        think(philo);
    }
    return (NULL);
}

// function that runs philo life and philo control
void eat_pray_love(t_table *table)
{
    pthread_t	control;

    pthread_create(&control, NULL, philo_control, table); 
    pthread_join(control, NULL);
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
