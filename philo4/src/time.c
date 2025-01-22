/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:56:38 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/22 19:40:58 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <complex.h>

//check the timeval
void check_timeval(pthread_mutex_t *mutex, struct timeval *time)
{
    pthread_mutex_lock(mutex);
    gettimeofday(time, NULL);
    pthread_mutex_unlock(mutex);
}

//get the timestamp
long get_timestamp(t_table *table)
{
    struct timeval current_time;
    long elapsed_ms;

    check_timeval(&table->table, &current_time);

    // Calculate the difference in seconds and microseconds
    long seconds_diff = (current_time.tv_sec - table->start_time.tv_sec) * 1000;
    long microseconds_diff = (current_time.tv_usec - table->start_time.tv_usec) / 1000;

    // Combine both to get the total elapsed time in milliseconds
    elapsed_ms = seconds_diff + microseconds_diff;

    return elapsed_ms;
}


//print the timestamp
void print_formatted_timestamp(long timestamp)
{
    //print in ms
    printf("%ldms ", timestamp);
}

//start the time
void ft_start_time(t_table *table)
{
    struct timeval start_time;
    
    if(gettimeofday(&start_time, NULL))
    {
        print_error("Error getting time");
        return ;
    }    
    table->start_time = start_time;
}

void	print_message(t_philo *philo, char *msg)
{
    long timestamp;
   
    if (philo->full)
        return ;
        
    timestamp = get_timestamp(philo->table);
    pthread_mutex_lock(&philo->table->write);
    if (!simulating(philo->table))
    {
        pthread_mutex_unlock(&philo->table->write);
        return ;
    }
    print_formatted_timestamp(timestamp);
    printf("Philosopher %d %s\n", philo->id, msg);
    pthread_mutex_unlock(&philo->table->write);    
}


