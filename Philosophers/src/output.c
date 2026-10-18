/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:42:13 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/23 17:42:14 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
	Thread-safe function to output the philosophers actions.
		Locks the mutex to prevent ouput from multiple threads.
		Checks if the sim ended before printing to avoid messages after death.
		Prints the message in the correct format <timestamp philo_id action>.
		Calculates times inside the mutex for it to always have the correct 
		order.

		The action string can be FORK, EAT, SLEEP and THINK.		
*/

void	output_actions(t_philo *philo, char *action)
{
	long	time;

	pthread_mutex_lock(&philo->table->lock_bool);
	if (!philo->table->end_sim)
	{
		time = get_time() - philo->table->start_sim;
		ft_putnbr_fd(time, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->id, 1);
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(action, 1);
	}
	pthread_mutex_unlock(&philo->table->lock_bool);
}

void	ft_putnbr_fd(long nbr, int fd)
{
	if (nbr > 9)
		ft_putnbr_fd(nbr / 10, fd);
	ft_putchar((nbr % 10) + '0', fd);
}

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write (fd, &str[i], 1);
		i++;
	}
}
