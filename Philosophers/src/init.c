/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:42:00 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/23 17:42:01 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
	Main init function.
		Returns INIT on error.
*/

int	init(char **av, t_table *table, t_philo **philo)
{
	if (ft_error(init_args(av, table), table, NULL) != 0)
		return (INIT);
	if (ft_error(init_forks(table), table, NULL) != 0)
		return (INIT);
	if (ft_error(init_philo(table, philo), table, *philo) != 0)
		return (INIT);
	return (0);
}

/*
	Init all arguments from t_table struct, besides forks.
		Returns MUTEX on error.
*/

int	init_args(char **av, t_table *table)
{
	table->nbr_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->meals_counter = -1;
	table->start_sim = get_time();
	table->end_sim = 0;
	table->forks = NULL;
	if (av[5])
		table->meals_counter = ft_atoi(av[5]);
	if (pthread_mutex_init(&table->output, NULL) != 0)
		return (MUTEX);
	if (pthread_mutex_init(&table->lock_bool, NULL) != 0)
		return (MUTEX);
	return (0);
}

/*
	Init forks from t_table struct.
		Returns MALLOC and MUTEX on error.
*/

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(table->nbr_philo * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (MALLOC);
	while (i < table->nbr_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			free_forks(table, i);
			return (MUTEX);
		}
		i++;
	}
	return (0);
}
/*
	Init t_philo struct.
		Return MALLOC on error.
*/

int	init_philo(t_table *table, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(table->nbr_philo * sizeof(t_philo));
	if (!*philo)
		return (MALLOC);
	while (i < table->nbr_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].meals_counter = 0;
		(*philo)[i].last_meal_time = table->start_sim;
		(*philo)[i].l_fork = &table->forks[i];
		(*philo)[i].r_fork = &table->forks[(i + 1) % table->nbr_philo];
		(*philo)[i].table = table;
		i++;
	}
	return (0);
}
