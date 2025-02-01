/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:56:38 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/30 18:23:06 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"
#include <sys/time.h>

// get the timestamp
long	get_timestamp_b(t_table_b *table)
{
	struct timeval	current_time;
	long			elapsed_ms;
	long			seconds_diff;

	gettimeofday(&current_time, NULL);
	seconds_diff = (current_time.tv_sec - table->start_time.tv_sec) * 1000;
	elapsed_ms = seconds_diff + (current_time.tv_usec / 1000)
		- (table->start_time.tv_usec / 1000);
	return (elapsed_ms);
}

// print the timestamp
void	print_formatted_timestamp_b(long timestamp)
{
	printf("%ld ", timestamp);
}

// start the time
void	ft_start_time_b(t_table *table)
{
	struct timeval	start_time;

	if (gettimeofday(&start_time, NULL))
	{
		print_error("Error getting time");
		return ;
	}
	table->start_time = start_time;
}

void	print_message_b(t_philo_b *philo, char *msg)
{
	long	timestamp;

	if (!philo->table->simulating)
		return ;
	timestamp = get_timestamp_b(philo->table);
	print_formatted_timestamp(timestamp);
	printf("Philosopher %d %s\n", philo->id, msg);
}
