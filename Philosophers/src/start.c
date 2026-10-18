/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:42:20 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/23 17:42:21 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <pthread.h>

/*
	Start of the simulation.
	
	Handling of the special case of only having one philosopher.
	Creates all the threads, monitors everything and joins all
		the threads when the simulation ends.
		Returns 1 on error.

*/

int	start(t_table *table, t_philo *philo)
{
	if (table->nbr_philo == 1)
		return (one_philo(table, philo));
	if (create_threads(table, philo) != 0)
		return (THREADS);
	monitoring_loop(table, philo);
	if (join_threads(table, philo) != 0)
		return (THREADS);
	return (0);
}

/*
	Handles the special case of only having one philo.
		Only one philo equals only one fork. Since the philo needs
		two forks to eat, it waits for time_to_die and prints the
		message for the death.
		Returns 1 to indicate failure and the death of the philo.
*/

int	one_philo(t_table *table, t_philo *philo)
{
	long	time;

	output_actions(philo, FORK);
	usleep(table->time_to_die * 1000);
	time = get_time() - table->start_sim;
	pthread_mutex_lock(&table->output);
	ft_putnbr_fd(time, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(DEAD, 1);
	pthread_mutex_unlock(&table->output);
	return (0);
}

/*
	Creates the thread for each philo.
		Iterates through all philosophers and creates and individual
		thread for each one. In case of any error creating a thread
		returns THREADS failure.
*/

int	create_threads(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, loop, &philo[i]) != 0)
			return (THREADS);
		i++;
	}
	return (0);
}

/*
	Waits for all the threads from philosophers to end its execution.
		Joins all threads, blocking until completion. This ensures that when
		the program exits there's a proper cleanup.
		Returns THREADS in case of error.

*/

int	join_threads(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (THREADS);
		i++;
	}
	return (0);
}
