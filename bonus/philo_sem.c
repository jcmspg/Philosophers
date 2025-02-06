/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:44:27 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/06 17:37:50 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

// function to check the death of the philosopher
bool	check_death_sem(t_philo_b *philo)
{
	long	time;

	time = get_timestamp_b(philo->table);
	if (time - philo->last_eat > philo->table->time_to_die)
	{
		sem_wait(philo->table->sem_print);
		philo->is_dead = true;
        philo->table->simulating = false;
		print_formatted_timestamp_b(time);
		printf("%d died\n", philo->id);
		sem_post(philo->table->sem_print);
		return (true);
	}
	return (false);
}

// routine function to check if the philosopher is dead
void	*eat_pray_love_b(void *arg)
{
	t_philo_b	*philo;

	philo = (t_philo_b *)arg;
    while (philo->table->simulating)
	{
        usleep(50);
		if (check_death_sem(philo))
        {
            sem_wait(philo->table->sem_print);
            exit(1);
        }
		if (philo->table->must_eat_count > 0
			&& philo->eat_count >= philo->table->must_eat_count)
		{
			philo->full = true;
            philo->table->simulating = false;
			exit(0);
		}
	}
    return (NULL);
}



void	monitor(t_philo_b *philo)
{
	if (pthread_create(&philo->thread, NULL, eat_pray_love_b, philo))
	{
		print_error_b("Error: Thread creation failed");
		exit(1);
	}
	philo->table->simulating = true;
	if (philo->id % 2 != 0)
	{
		print_philo(philo, "is thinking");
		usleep(50);
	}
	while (1)
	{
		sem_wait(philo->table->right_fork);
		print_philo(philo, "has taken a fork");
		sem_wait(philo->table->left_fork);
		print_philo(philo, "has taken a fork");
		print_philo(philo, "is eating");
		philo->last_eat = get_timestamp_b(philo->table);
		usleep(philo->table->time_to_eat * 1000);
		sem_post(philo->table->right_fork);
		sem_post(philo->table->left_fork);
		philo->eat_count++;
		print_philo(philo, "is sleeping");
		usleep(philo->table->time_to_sleep * 1000);
		print_philo(philo, "is thinking");
	}
	if (pthread_join(philo->thread, NULL))
	{
		print_error_b("Error: Thread join failed");
		exit(1);
	}
}

void	wrap_up(t_table_b *table)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < table->n_philos)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			j = 0;
			while (j < table->n_philos)
			{
				kill(table->philos[j]->philos_pid, SIGKILL);
				j++;
			}
			break ;
		}
		i++;
	}
	sem_close(table->extra);
	sem_close(table->right_fork);
	sem_close(table->left_fork);
	sem_close(table->sem_print);
	sem_unlink(SEM_EXTRA_NAME);
	sem_unlink(SEM_FORK_R_NAME);
	sem_unlink(SEM_FORK_L_NAME);
	sem_unlink(SEM_PRINT_NAME);
}
