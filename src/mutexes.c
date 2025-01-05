#include "../philo.h"
#include <bits/pthreadtypes.h>

//init the fork mutex
void init_forks(t_table *table)
{
    int i;

    table->forks = malloc(sizeof(pthread_mutex_t) * table->n_forks);
    if (!table->forks)
        print_error("Error creating forks");

    i = 0;
    while (i < table->n_forks)
    {
        if (pthread_mutex_init(&table->forks[i], NULL))
            print_error("Error initializing forks");
        i++;
    }
}

//free the fork mutex
void free_forks(t_table *table)
{
    int i;

    i = 0;
    if (!table->forks)
        return ;
    while (i < table->n_forks)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->forks);
}
