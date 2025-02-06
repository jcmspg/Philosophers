/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handlers2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:10:22 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 16:10:31 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	handle_long(pthread_mutex_t *mutex, long *status, long newstatus)
{
	pthread_mutex_lock(mutex);
	*status = newstatus;
	pthread_mutex_unlock(mutex);
}

long	check_long(pthread_mutex_t *mutex, long *status)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *status;
	pthread_mutex_unlock(mutex);
	return (ret);
}

bool	simulating(t_table *table)
{
	return (check_bool(&table->table, &table->simulating));
}
