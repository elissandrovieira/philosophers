/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:45:44 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/19 22:56:22 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INVALID_INPUT -1

# define RESET	"\033[0m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define BLUE	"\033[34m"
# define true	1
# define false	0

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
	unsigned int	id;
	unsigned int	is_in_use;
}	t_fork;

typedef struct  s_dining_data
{
	unsigned int	number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				number_of_meals;
	int				is_enough;
	pthread_mutex_t	get_enough;
	int				sync_n;
	pthread_mutex_t	sync;
	t_fork			*forks;
	long long		start_time;
}	t_dining_data;

typedef struct s_philo_data
{
	unsigned int	id;
	t_fork			*fork_r;
	t_fork			*fork_l;
	long long		last_meal_time;
	t_dining_data	*dining;
}	t_philo_data;

int	ft_atoi(const char *nptr);
int input_error(char *string);
int input_parser(int ac, char **av, t_dining_data	*dining);
t_fork *get_forks(int n_of_forks);
pthread_t	*get_philos(int n_of_philos, t_dining_data *dining);
long long	get_time(long long start_time);
int	set_mutexes(t_dining_data *dining);

void run_dining(t_philo_data *philo_data, long long start_time);

void	time_to_act(int action);
int	get_died(t_dining_data *dining);
int take_forks (t_philo_data *philo_data, long long start_time);
void leave_forks (t_philo_data *philo_data);

int	set_died(t_philo_data *philo_data, long long start_time);
int set_thinking (t_philo_data *philo_data, long long start_time);
int set_eating (t_philo_data *philo_data, long long start_time);
int set_sleeping (t_philo_data *philo_data, long long start_time);
#endif
