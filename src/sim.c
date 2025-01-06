/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:42:11 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/06 21:27:49 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	start_sim(t_table *table)
{
	table->simulating = true;
	start_threading(table);
}

//check if all philosophers ate
bool	check_all_ate(t_table *table)
{
    int	i;

    i = 0;
    while (i < table->n_philos)
    {
        if (table->philos[i].eat_count < table->must_eat_count)
            return (false);
        i++;
    }
    table->all_ate = true;
    return (true);
}


void	*sim_controler(void *arg)
{
	t_table		*table;
	int			i;
	long long	time;

	table = (t_table *)arg;
	i = 0;
	while (table->simulating)
	{
		pthread_mutex_lock(&table->deaths);
		time = get_timestamp(table);
		if (time - table->philos[i].last_eat > table->time_to_die)
		{
			print_formatted_timestamp(time);
			printf("Philosopher %d died\n", table->philos[i].id);
            free_table(table);
            exit(1);
			table->simulating = false;
			pthread_mutex_unlock(&table->deaths);
			return (NULL);
		}
		pthread_mutex_unlock(&table->deaths);
		if (check_all_ate(table))
        {
            table->simulating = false;
            return (NULL);
        }
		usleep(100);
        i++;
        if (i == table->n_philos)
            i = 0;
	}
	return (NULL);
}
