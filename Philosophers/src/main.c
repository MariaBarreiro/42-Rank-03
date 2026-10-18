/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:42:06 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/23 18:33:30 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
	Main function of the program.
		Returns 1 on error.
*/
int	main(int ac, char **av)
{
	t_table	table;
	t_philo	*philo;

	if (ft_error(parse_check(ac, av), NULL, NULL) != 0)
		return (1);
	if (ft_error(init(av, &table, &philo), &table, philo) != 0)
		return (1);
	if (ft_error(start(&table, philo), &table, philo) != 0)
		return (1);
	ft_error(-1, &table, philo);
	return (0);
}
