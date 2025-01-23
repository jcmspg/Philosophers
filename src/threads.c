/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:25:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/23 23:29:28 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_t	*init_thread_array(t_table *table)
{
	pthread_t	*thread_array;

	thread_array = malloc(sizeof(pthread_t) * table->n_philos);
	if (!thread_array)
		return (NULL);
	memset(thread_array, 0, sizeof(pthread_t) * table->n_philos);
	return (thread_array);
}

bool	check_if_dead(t_philo *philo)
{
	long	current_time;

	current_time = get_timestamp(philo->table);
	if (current_time - philo->last_eat > philo->table->time_to_die)
	{
		handle_bool(&philo->table->death_mutex, &philo->is_dead, true);
		print_message(philo, "died");
		handle_bool(&philo->table->table, &philo->table->simulating, false);
		return (true);
	}
	return (false);
}

void	sleeperino(t_philo *philo)
{
	if (check_if_dead(philo))
		return ;
	print_message(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void	grab_forks(t_philo *philo)
{
	if (check_if_dead(philo))
		return ;
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	print_message(philo, "has taken first fork");
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_message(philo, "has taken second fork");
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
}

void	eat(t_philo *philo)
{
	if (check_if_dead(philo))
		return ;
	grab_forks(philo);
	print_message(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	handle_long(&philo->table->table, &philo->last_eat,
		get_timestamp(philo->table));
	handle_int(&philo->table->table, &philo->eat_count, philo->eat_count + 1);
	if (philo->table->must_eat_count > 0
		&& philo->eat_count == philo->table->must_eat_count)
		handle_bool(&philo->table->table, &philo->full, true);
	release_forks(philo);
}

// think and wait until the other philosophers finish eating
void	think(t_philo *philo)
{
	if (check_if_dead(philo))
		return ;
	print_message(philo, "is thinking");
	if (check_if_dead(philo))
		return ;
}

// routine for the philosophers
void	*eat_pray_love(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_sync(philo->table);
	while (simulating(philo->table))
	{
		if (check_if_dead(philo))
			return (NULL);
		if (check_bool(&philo->table->table, &philo->full))
			return (NULL);
		if (philo->id % 2 != 0)
			think(philo);
		eat(philo);
		sleeperino(philo);
		think(philo);
	}
	return (NULL);
}

// function to join all threads
void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_join(table->thread_array[i], NULL);
		i++;
	}
}
pthread_t	create_thread(t_philo *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, eat_pray_love, philo))
	{
		free_thread_array(philo->table);
		print_error("Error creating thread");
		return (0);
	}
	return (thread);
}

// start simulation
void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->thread_array[i] = create_thread(&table->philos[i]);
		if (table->thread_array[i] == 0)
			return ;
		i++;
	}
}
