/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:46:11 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/02 21:30:07 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_philo(t_philo *philo)
{
	if (!philo)
		return ;
	free(philo);
}

void    free_philos(t_table *table)
{
    int i;

    i = 0;
    while (i < table->n_philos)
    {
        free_philo(table->philos[i]);
        i++;
    }
    free(table->philos);
}


t_philo	*create_philo(int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo->id = id;
	return (philo);
}

t_philo	**autobots_assemble(t_table *table)
{
    int i;
    t_philo **philos;

    i = 0;
    philos = malloc(sizeof(t_philo *) * (table->n_philos + 1));
    if (!philos)
        return (NULL);
    memset(philos, 0, sizeof(t_philo *) * table->n_philos);
    while (i < table->n_philos)
    {
        philos[i] = create_philo(i + 1);
        if (!philos[i])
        {
            free_philo(philos[i]);
            free_philos(table);
            return (NULL);
        }
        i++;
    }
    return (philos);
}
