/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:42:17 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/23 17:42:17 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
	Check for empty arguments.
		Returns INVALID_ARGS in case of error.
*/
int	empty_check(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i][0] == '\0')
			return (INVALID_ARGS);
		i++;
	}
	return (0);
}

/*
	Check for correct number of args and for the use of only numbers.
		Returns WRONG_USAGE or INVALID_ARGS in case of error.
*/

int	arg_check(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ac != 5 && ac != 6)
		return (WRONG_USAGE);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (INVALID_ARGS);
			j++;
		}
		i++;
	}
	return (0);
}

/*
	Check for INT_MAX and INT_MIN and for invalid args such as 0
		or negative numbers.
		Returns INVALID_ARGS on error.
*/
int	limits_check(char **av)
{
	int		i;
	int		j;
	long	arg;

	i = 1;
	while (av[i])
	{
		arg = 0;
		j = 0;
		while (av[i][j])
		{
			arg = (arg * 10) + (av[i][j] - '0');
			if (arg > INT_MAX)
				return (INVALID_ARGS);
			j++;
		}
		if (arg == 0)
			return (INVALID_ARGS);
		if (arg < 0)
			return (INVALID_ARGS);
		i++;
	}
	return (0);
}

/*
	Main parsing function.
		Returns 1 on error.
*/

int	parse_check(int ac, char **av)
{
	if (ft_error(empty_check(av), NULL, NULL) != 0)
		return (1);
	if (ft_error(arg_check(ac, av), NULL, NULL) != 0)
		return (1);
	if (ft_error(limits_check(av), NULL, NULL) != 0)
		return (1);
	return (0);
}
