/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:42:03 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/23 17:42:04 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <pthread.h>

/*
	Main loop for each thread to execute the routine.
		Implements the eat->sleep->think and correctly
		outputs the action into the terminal. While always
		checking if the simulation has ended after each action.
		In case of an odd number of philosophers, adds a delay
		to half of them to break synchronization.
*/

void	*loop(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (stop_check(philo) == 0)
	{
		eat(philo);
		if (stop_check(philo) == 1 || done_eating(philo) == 1)
			break ;
		output_actions(philo, SLEEP);
		usleep(philo->table->time_to_sleep * 1000);
		if (stop_check(philo) == 1)
			break ;
		output_actions(philo, THINK);
		if (philo->table->nbr_philo % 2 != 0
			&& philo->id % 2 != 0)
			usleep(1000);
	}
	return (NULL);
}

/*
	Check if the simulation has ended.
		If the return is 0, simulation has NOT ended.
		If anything besides that, simulation HAS ended.
*/

int	stop_check(t_philo *philo)
{
	int	has_simulation_ended;

	pthread_mutex_lock(&philo->table->lock_bool);
	has_simulation_ended = philo->table->end_sim;
	pthread_mutex_unlock(&philo->table->lock_bool);
	return (has_simulation_ended);
}

/*
	Handling of the eating proccess for each philosopher.
		Takes forks, updates the meal time, checks if there's
		a meal_counter, simulates eating time and releases the forks.
*/

void	eat(t_philo *philo)
{
	take_fork(philo);
	output_actions(philo, EATING);
	pthread_mutex_lock(&philo->table->lock_bool);
	philo->last_meal_time = get_time();
	if (philo->table->meals_counter > 0)
		philo->meals_counter += 1;
	pthread_mutex_unlock(&philo->table->lock_bool);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

/*
	Handling of the forks for each time a philo eats.
		In case of the philo_id being even, he takes the right
		fork first. In case of odd, the left fork is taken first.
*/

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		output_actions(philo, FORK);
		pthread_mutex_lock(philo->l_fork);
		output_actions(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		output_actions(philo, FORK);
		pthread_mutex_lock(philo->r_fork);
		output_actions(philo, FORK);
	}
}

/*
	Check if the philo is done eating.
		Check done right after eating to prevent unecessary
		routines. Checks if the number of meals the philo
		has eaten is the same as the meals needed.
*/

int	done_eating(t_philo *philo)
{
	int	finished_eating;

	pthread_mutex_lock(&philo->table->lock_bool);
	finished_eating = 0;
	if (philo->meals_counter > 0
		&& philo->meals_counter == philo->table->meals_counter)
		finished_eating = 1;
	pthread_mutex_unlock(&philo->table->lock_bool);
	return (finished_eating);
}
