/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:25:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/22 21:14:12 by joao             ###   ########.fr       */
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

void	sleeperino(t_table *table)
{
	long	start;
	long	end;

	start = get_timestamp(table);
	end = start + table->time_to_sleep;
    if (end - start > table->time_to_die)
	{
		handle_bool(&table->table, &table->philos->is_dead, true);
		print_message(table->philos, "died");
		return ;
	}
	while (get_timestamp(table) < end)
	{

		if (!simulating(table))
			break ;
		usleep(100);
	}
}

void	eat(t_table *table)
{
	long	start;
	long	end;

	start = get_timestamp(table);
	end = start + table->time_to_eat;
    while (get_timestamp(table) < end)
    {
        if (!simulating(table))
            break ;      
    }

}

// think and wait until the other philosophers finish eating
void	think(t_table *table)
{
    long	start;
    long	end;
    long    time;

    time = 100;
    start = get_timestamp(table);
    end = start + time;
	while(get_timestamp(table) < end)
    {
        if (!simulating(table))
            break ;
        usleep(100);
    }
}

void grab_forks(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
    print_message(philo, "has taken right fork");
    pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    print_message(philo, "has taken left fork");
}

// routine for the philosophers
void	*eat_pray_love(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_sync(philo->table);
	while (simulating(philo->table))
	{
		if (philo->full)
			break ;
		if (philo->is_dead)
			break ;
        //grab the forks
        think(philo->table);
        grab_forks(philo);
        print_message(philo, "has taken both forks");
		print_message(philo, "is eating");
		eat(philo->table);
		print_message(philo, "is sleeping");
		sleeperino(philo->table);
		print_message(philo, "is thinking");
		think(philo->table);
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
        i++;
    }
}
