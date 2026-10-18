/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:41:46 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/23 18:59:40 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define WRONG_USAGE	1
# define INVALID_ARGS 2
# define MUTEX 3
# define INIT 4
# define MALLOC 5
# define THREADS 6

# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"
# define RESET   "\033[0m"

# define DEAD "\033[31mdied\033[0m\n"
# define FORK "\033[35mhas taken a fork\033[0m\n"
# define EATING "is eating\n"
# define SLEEP "\033[33mis sleeping\033[0m\n"
# define THINK "\033[32mis thinking\033[0m\n"

//Structs//

typedef struct s_table
{
	long			nbr_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_counter;
	long			start_sim;
	int				end_sim;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
	pthread_mutex_t	lock_bool;
}	t_table;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	long				last_meal_time;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			thread;
	t_table				*table;
}	t_philo;

//Parsing//
int		parse_check(int ac, char **av);
int		emtpy_check(char **av);
int		arg_check(int ac, char **av);
int		limits_check(char **av);

//Init//
int		init(char **av, t_table *table, t_philo **philo);
int		init_args(char **av, t_table *table);
int		init_forks(t_table *table);
int		init_philo(t_table *table, t_philo **philo);

//Start//
int		start(t_table *table, t_philo *philo);
int		one_philo(t_table *table, t_philo *philo);
int		create_threads(t_table *table, t_philo *philo);
int		join_threads(t_table *table, t_philo *philo);

//Loop//
void	*loop(void *_philo);
int		stop_check(t_philo *philo);
void	eat(t_philo *philo);
void	take_fork(t_philo *philo);
int		done_eating(t_philo *philo);

//Monitoring Loop//
void	monitoring_loop(t_table *table, t_philo *philo);
int		check_starvation(t_philo *philo);
int		check_required_meals(t_table *table, t_philo *philo);
void	death_message(t_philo *philo, long timestamp);

//Error//
int		ft_error(int error_type, t_table *table, t_philo *philo);
void	error_message(int type);

//Utils//
long	get_time(void);
int		ft_atoi(const char *nptr);

//Output//
void	output_actions(t_philo *philo, char *action);
void	ft_putnbr_fd(long nbr, int fd);
void	ft_putchar(char c, int fd);
void	ft_putstr_fd(char *str, int fd);

//Free//
void	free_forks(t_table *table, int i);

#endif
