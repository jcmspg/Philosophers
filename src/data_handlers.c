/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:21:43 by joao              #+#    #+#             */
/*   Updated: 2025/01/29 16:13:36 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// functions to handle the data read and write from mutexes
void	handle_bool(pthread_mutex_t *mutex, bool *status, bool newstatus)
{
	pthread_mutex_lock(mutex);
	*status = newstatus;
	pthread_mutex_unlock(mutex);
}

bool	check_bool(pthread_mutex_t *mutex, bool *status)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *status;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	handle_int(pthread_mutex_t *mutex, int *status, int newstatus)
{
	pthread_mutex_lock(mutex);
	*status = newstatus;
	pthread_mutex_unlock(mutex);
}

int	check_int(pthread_mutex_t *mutex, int *status)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *status;
	pthread_mutex_unlock(mutex);
	return (ret);
}
