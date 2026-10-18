/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:41:38 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/23 17:41:43 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <pthread.h>

/*
	Main monitoring loop that monitors all philosophers.
	Checks if any philo died for starvation or if any has eaten the required
	number of meals.
	Runs in the MAIN THREAD while each philosopher thread executes. As soon
	as any of the conditions above equals 1, the flag for the end_sim is changed
	and returns.
*/

void	monitoring_loop(t_table *table, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->nbr_philo)
		{
			if (check_starvation(&philo[i]))
				return ;
			i++;
		}
		if (check_required_meals(table, philo))
			return ;
		usleep(1000);
	}
}

/*
	Checks if any philosopher died of starvation.
		The time_to_die is compared with the time since the last meal.
		In case of the philo being dead, the flag of the end_sim is changed
		and the death message is printed with the respective timestamp.
*/

int	check_starvation(t_philo *philo)
{
	long	curr_time;
	long	timestamp;
	long	last_meal;

	pthread_mutex_lock(&philo->table->lock_bool);
	curr_time = get_time();
	last_meal = philo->last_meal_time;
	if (curr_time - last_meal > philo->table-> time_to_die)
	{
		philo->table->end_sim = 1;
		timestamp = curr_time - philo->table->start_sim;
		pthread_mutex_unlock(&philo->table->lock_bool);
		death_message(philo, timestamp);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->lock_bool);
	return (0);
}

/*
	Prints the death message.
		Prints in the following format: timestamp_in_ms X died
*/

void	death_message(t_philo *philo, long timestamp)
{
	pthread_mutex_lock(&philo->table->output);
	ft_putnbr_fd(timestamp, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(philo->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(DEAD, 1);
	pthread_mutex_unlock(&philo->table->output);
}

/*
	Checks if philosophers have eaten enough meals.
		Checks all philosophers to see how many of them have eaten
		the meals required.
*/

int	check_required_meals(t_table *table, t_philo *philo)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (table->meals_counter <= 0)
		return (0);
	pthread_mutex_lock(&table->lock_bool);
	while (i < table->nbr_philo)
	{
		if (philo[i].meals_counter >= table->meals_counter)
			counter++;
		i++;
	}
	if (counter == table->nbr_philo)
	{
		table->end_sim = 1;
		pthread_mutex_unlock(&table->lock_bool);
		usleep(1000);
		return (1);
	}
	pthread_mutex_unlock(&table->lock_bool);
	return (0);
}
