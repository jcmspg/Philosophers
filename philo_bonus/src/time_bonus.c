/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:56:38 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/06 17:39:51 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

// get the timestamp
long	get_timestamp_b(t_table_b *table)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)
		- (table->start_time.tv_sec * 1000) - (table->start_time.tv_usec
			/ 1000));
}

// print the timestamp
void	print_formatted_timestamp_b(long timestamp)
{
	printf("%ld ", timestamp);
}

// start the time
void	ft_start_time_b(t_table_b *table)
{
	if (gettimeofday(&table->start_time, NULL) == -1)
	{
		print_error_b("Error getting time");
		return ;
	}
}
