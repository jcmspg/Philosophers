/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:56:38 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/17 21:22:56 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <complex.h>

//get the timestamp
long get_timestamp(t_table *table)
{
    struct timeval tv;
    long elapsed_ms;


    gettimeofday(&tv, NULL);
    elapsed_ms = (tv.tv_sec - table->start_time.tv_sec) * 1000;
    elapsed_ms += (tv.tv_usec - table->start_time.tv_usec) / 1000;
    

    return (elapsed_ms);
}

//print the timestamp
void print_formatted_timestamp(long timestamp)
{
//    long hours;
//    long minutes;
//    long seconds;
    long milliseconds;

//    hours = timestamp / 3600000;
//    minutes = (timestamp % 3600000) / 60000;
//    seconds = ((timestamp % 3600000) % 60000) / 1000;
    milliseconds = ((timestamp % 3600000) % 60000) % 1000;

    // print only in ms
    printf("%ld ", milliseconds);
    
    // print in hh:mm:ss:ms
    //printf("%02ld:%02ld:%02ld:%03ld ", hours, minutes, seconds, milliseconds);
}

//start the time
void ft_start_time(t_table *table)
{
    gettimeofday(&table->start_time, NULL);
}

void	print_message(t_philo *philo, char *msg)
{
	if (philo->table->simulating == false)
		return ;
	pthread_mutex_lock(&philo->table->write);
	print_formatted_timestamp(get_timestamp(philo->table));
	printf("Philosopher %d %s\n", philo->id, msg);
	pthread_mutex_unlock(&philo->table->write);
}


