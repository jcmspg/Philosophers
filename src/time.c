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

void print_formatted_timestamp(long timestamp)
{
    long hours;
    long minutes;
    long seconds;
    long milliseconds;

    hours = timestamp / 3600000;
    minutes = (timestamp % 3600000) / 60000;
    seconds = ((timestamp % 3600000) % 60000) / 1000;
    milliseconds = ((timestamp % 3600000) % 60000) % 1000;

    printf("%02ld:%02ld:%02ld:%03ld ", hours, minutes, seconds, milliseconds);
}

void ft_start_time(t_table *table)
{
    gettimeofday(&table->start_time, NULL);
}
