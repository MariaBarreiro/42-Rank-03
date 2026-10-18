/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:41:53 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/23 18:32:16 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <pthread.h>

void	error_message(int type)
{
	if (type == INVALID_ARGS)
		write (2, "Invalid arguments.\n", 19);
	else if (type == WRONG_USAGE)
	{
		write (2, "Usage: ./philo <number_of_philosophers> <time_to_die>", 53);
		write (2, " <time_to_eat> <time_to_sleep> ", 31);
		write (2, "[number_of_times_each_philosopher_must_eat].\n", 45);
	}
	else if (type == MUTEX)
		write (2, "Mutex error.\n", 13);
	else if (type == INIT)
		write (2, "Initialization error.\n", 22);
	else if (type == MALLOC)
		write (2, "Malloc error\n", 13);
	else if (type == THREADS)
		write (2, "Thread error.\n", 14);
	return ;
}

int	ft_error(int error_type, t_table *table, t_philo *philo)
{
	if (error_type != 0 && error_type != INIT)
	{
		if (table)
		{
			if (error_type == THREADS || error_type == MALLOC
				|| error_type == MUTEX)
			{
				pthread_mutex_destroy(&table->output);
				pthread_mutex_destroy(&table->lock_bool);
			}
			if (table && table->forks)
				free_forks(table, table->nbr_philo);
		}
		if (philo)
			free (philo);
	}
	if (error_type <= 0)
		return (0);
	error_message(error_type);
	return (1);
}
