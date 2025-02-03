#include "../philo_bonus.h"

t_philo_b	*create_philo_b(t_table_b *table, int id)
{
	t_philo_b	*philo;

	philo = (t_philo_b *)malloc(sizeof(t_philo_b));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo_b));
	philo->id = id + 1;
	philo->table = table;
	philo->eat_count = 0;
	philo->last_eat = 0;
	philo->full = false;
	philo->is_dead = false;
	philo->left_fork = table->sem_forks;
	philo->right_fork = table->sem_forks;
	philo->sem_print = table->sem_print;
	return (philo);
}

void	create_philos(t_table_b *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
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

void	forking_philos(t_table_b *table)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < table->n_philos)
	{
		pid = fork();
		if (pid == 0)
		{
            while(1)
            {
                philo_life_sem(table->philos[i]);
            }
		}
		i++;
	}
	i = 0;
	while (i < table->n_philos)
	{
		wait(NULL);
		i++;
	}
}
