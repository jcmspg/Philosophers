#include "../philo_bonus.h"

int *prepare_eating(t_table_b *table)
{
    int *eating_indexes;
    int i;

    eating_indexes = (int *)malloc(sizeof(int) * table->group_size);
    if (!eating_indexes)
        return (NULL);
    i = 0;
    while (i < table->group_size)
    {
        eating_indexes[i] = i + 1;
        i++;
    }
    return (eating_indexes);
}

bool set_eating_indexes (t_table_b *table)
{
    table->eating_indexes = prepare_eating(table);
    if (!table->eating_indexes)
    {
        printf("Error: Failed to prepare eating indexes\n");
        return (false);
    }
    return (true);
}

void rotate_eating_group(t_table_b *table, int round)
{
    int start;
    int i;

    start = (round * table->group_size) % table->n_philos;
    i = 0;
    while (i < table->group_size)
    {
        table->eating_indexes[i] = (start + i) % table->n_philos + 1;
        i++;
    }
}
