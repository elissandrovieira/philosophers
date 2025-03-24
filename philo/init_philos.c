/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:28:10 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/24 19:54:45 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	malloc_threads(t_thread_list **threads, int n_of_philos)
{
	*threads = malloc(sizeof(t_thread_list));
	if (!*threads)
		return (FALSE);
	(*threads)->philos = malloc(sizeof(pthread_t) * n_of_philos);
	(*threads)->monitor = malloc(sizeof(pthread_t));
	if (!(*threads)->philos || !(*threads)->monitor)
	{
		free(*threads);
		return (FALSE);
	}
	(*threads)->philo_data = malloc(sizeof(t_philo_data) * n_of_philos);
	if (!(*threads)->philo_data)
	{
		free((*threads)->philos);
		free((*threads)->monitor);
		free(*threads);
		return (FALSE);
	}
	return (TRUE);
}

static void	init_threads(t_thread_list **threads, t_dining_data *dining)
{
	int	n_of_philos;
	int	i;

	n_of_philos = dining->number_of_philos;
	i = 0;
	while (i < n_of_philos)
	{
		(*threads)->philo_data[i].id = i + 1;
		(*threads)->philo_data[i].dining = dining;
		(*threads)->philo_data[i].last_meal_time = 0;
		(*threads)->philo_data[i].thinking = FALSE;
		(*threads)->philo_data[i].fork_r = &dining->forks[i];
		if (i == n_of_philos - 1 && n_of_philos != 1)
			(*threads)->philo_data[i].fork_l = &dining->forks[0];
		else
			(*threads)->philo_data[i].fork_l = &dining->forks[i + 1];
		pthread_create(&(*threads)->philos[i], NULL, philo_routine,
			(void *)&(*threads)->philo_data[i]);
		i++;
	}
	pthread_create((*threads)->monitor, NULL, monitor_routine,
		(void *)(*threads)->philo_data);
}

t_thread_list	*init_philos(t_dining_data *dining)
{
	t_thread_list	*threads;
	int				n_of_philos;
	int				i;

	threads = NULL;
	n_of_philos = dining->number_of_philos;
	i = 0;
	malloc_threads(&threads, n_of_philos);
	init_threads(&threads, dining);
	return (threads);
}
