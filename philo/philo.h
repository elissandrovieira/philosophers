/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:45:44 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/24 18:59:49 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INVALID_INPUT -1

# define RESET	"\033[0m"
# define RED	"\033[31m"
# define GREEN	"\033[32m"
# define BLUE	"\033[34m"
# define TRUE	1
# define FALSE	0

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	fork;
	pthread_mutex_t	is_in_use_m;
	unsigned int	is_in_use;
}	t_fork;

typedef struct s_dining_data
{
	unsigned int	number_of_philos;
	pthread_mutex_t	number_of_philos_m;
	unsigned int	time_to_die;
	pthread_mutex_t	time_to_die_m;
	unsigned int	time_to_eat;
	pthread_mutex_t	time_to_eat_m;
	unsigned int	time_to_sleep;
	pthread_mutex_t	time_to_sleep_m;
	int				number_of_meals;
	pthread_mutex_t	number_of_meals_m;
	int				is_enough;
	pthread_mutex_t	is_enough_m;
	int				sync_m;
	pthread_mutex_t	sync_m_m;
	pthread_mutex_t	print;
	t_fork			*forks;
	long long		start_time;
	pthread_mutex_t	start_time_m;
}	t_dining_data;

typedef struct s_philo_data
{
	unsigned int	id;
	unsigned int	thinking;
	t_fork			*fork_r;
	t_fork			*fork_l;
	long long		last_meal_time;
	t_dining_data	*dining;
}	t_philo_data;

typedef struct s_mutex_order
{
	t_fork	*first;
	t_fork	*second;
}	t_mutex_order;

typedef struct s_thread_list
{
	pthread_t		*philos;
	pthread_t		*monitor;
	t_philo_data	*philo_data;
}	t_thread_list;

int				ft_atoi(const char *nptr);
int				input_error(char *string);
int				input_parser(int ac, char **av, t_dining_data	*dining);
t_fork			*init_forks(int n_of_forks);
t_dining_data	*init_dining(int ac, char **av);
int				init_mutexes(t_dining_data *dining);
t_thread_list	*init_philos(t_dining_data *dining);
long long		get_time(long long start_time);

void			*philo_routine(void *arg);
void			*monitor_routine(void *arg);


void			time_to_act(int action);
int				get_died(t_dining_data *dining);
int				take_forks(t_philo_data *philo_data, long long start_time);
void			leave_forks(t_philo_data *philo_data);
t_mutex_order	mutex_order(t_fork *first, t_fork *second);
void			print_message(t_philo_data *philo_data,
	long long start_time, char *message);

int				set_died(t_philo_data *philo_data, long long start_time);
int				set_thinking(t_philo_data *philo_data, long long start_time);
int				set_eating(t_philo_data *philo_data, long long start_time);
int				set_sleeping(t_philo_data *philo_data, long long start_time);

void			destroy_mutexes(t_dining_data *dining);
void	destroy_allocs(t_dining_data *dining, t_thread_list *threads);
#endif
