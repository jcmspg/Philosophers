/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:56:38 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/04 20:18:23 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

// check the timeval
void	check_timeval(struct timeval *time, t_table_b *table)
{
    gettimeofday(time, NULL);
}

// get the timestamp
long	get_timestamp_b(t_table_b *table)
{
	struct timeval	current_time;
	long			elapsed_ms;
	long			seconds_diff;

	check_timeval(&current_time, table);
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
void	ft_start_time_b(t_table_b *table)
{
	struct timeval	start_time;

	if (gettimeofday(&start_time, NULL))
	{
		print_error_b("Error getting time");
		return ;
	}
	table->start_time = start_time;
}

void print_message_b(t_philo_b *philo, char *msg)
{
    long	timestamp;

    sem_wait(philo->table->sem_print);
    timestamp = get_timestamp_b(philo->table);
    print_formatted_timestamp(timestamp);
    printf("%d %s\n", philo->id, msg);
    sem_post(philo->table->sem_print);
}
