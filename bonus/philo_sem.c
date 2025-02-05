/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:44:27 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/05 02:45:17 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"


// function to check the death of the philosopher
bool	check_death_sem(t_philo_b *philo)
{
	if (get_timestamp_b(philo->table) - philo->last_eat > philo->table->time_to_die)
		return (true);
	return (false);
}

// routine function to check if the philosopher is dead
void	*eat_pray_love_b(void *arg)
{
	t_philo_b	*philo;

	philo = (t_philo_b *)arg;
	while (!philo->table->simulating)
	{
		usleep(100);
		if (check_death_sem(philo))
		{
			philo->is_dead = true;
			sem_wait(philo->table->sem_print);
			print_philo(philo, "died");
			philo->table->simulating = false;
			break;
		}
		if (philo->table->must_eat_count > 0
			&& philo->eat_count >= philo->table->must_eat_count)
		{
			philo->full = true;
			break ;
		}
	}
	if (philo->is_dead)
		exit(1);
	else
		exit(0);
}

void	monitor(t_philo_b *philo)
{
	if (pthread_create(&philo->thread, NULL, eat_pray_love_b, philo))
		{
			print_error_b("Error: Thread creation failed");
			exit(0);
		}
	if (philo->id % 2 != 0)
		usleep(100);
	while (1)
	{
		print_philo(philo, "is thinking");
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
	}
	if (pthread_join(philo->thread, NULL))
	{
		print_error_b("Error: Thread join failed");
		exit(0);
	}
}

void wrap_up(t_table_b *table)
{
	int i;
	int status;

	i = 0;
	while (i < table->n_philos)
	{
		waitpid(table->philos[i]->philos_pid, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < table->n_philos)
			{
				kill(table->philos[i]->philos_pid, SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
	sem_close(table->right_fork);
	sem_close(table->left_fork);
	sem_close(table->sem_print);
	sem_unlink(SEM_FORK_R_NAME);
	sem_unlink(SEM_FORK_L_NAME);
	sem_unlink(SEM_PRINT_NAME);
}