/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:56:37 by joamiran          #+#    #+#             */
/*   Updated: 2025/01/29 16:56:08 by joamiran         ###   ########.fr       */
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
	table->n_philos = ft_atoi(argv[1]);
	table->time_to_die = (ft_atoi(argv[2]));
	table->time_to_eat = (ft_atoi(argv[3]));
	table->time_to_sleep = (ft_atoi(argv[4]));
	table->n_forks = table->n_philos;
	if (argv[5])
		table->must_eat_count = ft_atoi(argv[5]);
	else
		table->must_eat_count = 0;
}
