/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:45:44 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/12 00:57:08 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INVALID_INPUT -1

# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct  s_dining_data
{
	unsigned int	number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				number_of_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sync;
}	t_dining_data;


typedef struct s_philo_data
{
	unsigned int	id;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	t_dining_data	*dining;
}	t_philo_data;

int	ft_atoi(const char *nptr);
int input_error(char *string);
int input_parser(int ac, char **av, t_dining_data	*dining);


#endif
