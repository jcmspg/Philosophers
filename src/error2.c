/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:20:06 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 16:20:53 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_results(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		printf("Philosopher %d ate %d times\n", table->philos[i].id,
			table->philos[i].eat_count);
		i++;
	}
}
