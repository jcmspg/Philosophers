#include "../philo_bonus.h"

void free_table_b(t_table_b *table)
{
    int i;

    i = 0;
    if (table->philos)
    {
        while (i < table->n_philos)
        {
            free(table->philos[i]);
            i++;
        }
        free(table->philos);
    }
    free(table);
}
