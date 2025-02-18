/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:56:37 by joamiran          #+#    #+#             */
/*   Updated: 2025/02/18 21:43:22 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	result;

	if (!str)
		return (0);
	if (ft_strlen(str) > 10)
		return (0);
	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

void	assign_values(t_table *table, char **argv)
{
	int	i;

	i = 0;
	table->n_philos = ft_atoi(argv[1]);
	table->time_to_die = (ft_atoi(argv[2]));
	table->time_to_eat = (ft_atoi(argv[3]));
	table->time_to_sleep = (ft_atoi(argv[4]));
	table->n_forks = table->n_philos;
	if (argv[5])
	{
		i = ft_atoi(argv[5]);
		if (i < 0)
			table->must_eat_count = -2;
		else
			table->must_eat_count = i;
	}
	else
		table->must_eat_count = -1;
}

void	print_dead(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->table->write);
	if (check_bool(&philo->table->table, &philo->is_dead) == true
		|| check_bool(&philo->table->table, &philo->table->simulating) == false)
		return (pthread_mutex_unlock(&philo->table->write), (void)0);
	timestamp = get_timestamp(philo->table);
	print_formatted_timestamp(timestamp);
	printf("%d died\n", philo->id + 1);
	handle_bool(&philo->table->table, &philo->table->simulating, false);
	pthread_mutex_unlock(&philo->table->write);
}
