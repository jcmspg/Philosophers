#include "../philo_bonus.h"

t_philo_b *create_philo_b(t_table_b *table, int id)
{
    t_philo_b	*philo;

    philo = (t_philo_b *)malloc(sizeof(t_philo_b));
    if (!philo)
        return (NULL);
    memset(philo, 0, sizeof(t_philo_b));
    philo->id = id;
    philo->table = table;
    philo->eat_count = 0;
    philo->last_eat = 0;
    philo->full = false;
    philo->can_eat = false;
    philo->is_dead = false;
    return (philo);
}

void create_philos(t_table_b *table)
{
    int i;

    i = 1;
    while (i <= table->n_philos)
    {
        table->philos[i] = create_philo_b(table, i);
        if (!table->philos[i])
        {
            free(table->philos);
            return ;
        }
        i++;
    }
}

void forking_philos(t_table_b *table)
{
    int i;
    pid_t pid;

    i = 1;
    init_semaphore(table);
    while (i <= table->n_philos)
    {
        table->philos[i]->id = i;
        pid = fork();

        if (pid < 0)
        {
            printf("Error: fork failed\n");
            exit(1);
        }
        if (pid == 0)
        {
            philo_life_b(table->philos[i]);
            exit(0);
        }
        i++;
    }
}
