/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:56:38 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/18 21:40:20 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// check the timeval
void	check_timeval(pthread_mutex_t *mutex, struct timeval *time)
{
	pthread_mutex_lock(mutex);
	gettimeofday(time, NULL);
	pthread_mutex_unlock(mutex);
}

// get the timestamp
long	get_timestamp(t_table *table)
{
	struct timeval	current_time;
	long			elapsed_ms;
	long			seconds_diff;

	check_timeval(&table->table, &current_time);
	seconds_diff = (current_time.tv_sec - table->start_time.tv_sec) * 1000;
	elapsed_ms = seconds_diff + (current_time.tv_usec / 1000)
		- (table->start_time.tv_usec / 1000);
	return (elapsed_ms);
}

// print the timestamp
void	print_formatted_timestamp(long timestamp)
{
	printf("%ld ", timestamp);
}

// start the time
void	ft_start_time(t_table *table)
{
	struct timeval	start_time;

	if (gettimeofday(&start_time, NULL))
	{
		print_error("Error getting time");
		return ;
	}
	table->start_time = start_time;
}

void	print_message(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->write);
	timestamp = get_timestamp(philo->table);
	if (check_bool(&philo->table->table, &philo->table->simulating) == false)
		return (pthread_mutex_unlock(&philo->table->write), (void)0);
	print_formatted_timestamp(timestamp);
	printf("%d %s\n", philo->id + 1, msg);
	pthread_mutex_unlock(&philo->table->write);
}
