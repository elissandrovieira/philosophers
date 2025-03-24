/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:14:20 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/24 19:51:56 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_dining_data *dining)
{
	unsigned int	i;
	unsigned int	number_of_philos;

	i = 0;
	number_of_philos = dining->number_of_philos;
	pthread_mutex_destroy(&dining->sync_m_m);
	pthread_mutex_destroy(&dining->is_enough_m);
	pthread_mutex_destroy(&dining->print);
	pthread_mutex_destroy(&dining->number_of_meals_m);
	pthread_mutex_destroy(&dining->number_of_philos_m);
	pthread_mutex_destroy(&dining->start_time_m);
	pthread_mutex_destroy(&dining->time_to_die_m);
	pthread_mutex_destroy(&dining->time_to_eat_m);
	pthread_mutex_destroy(&dining->time_to_sleep_m);
	while (i < number_of_philos)
	{
		pthread_mutex_destroy(&dining->forks[i].fork);
		pthread_mutex_destroy(&dining->forks[i++].is_in_use_m);
	}
}

void	destroy_allocs(t_dining_data *dining, t_thread_list *threads)
{
	free(dining->forks);
	free(dining);
	free(threads->philo_data);
	free(threads->philos);
	free(threads->monitor);
	free(threads);
}
