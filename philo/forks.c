/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:46:32 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/19 22:55:29 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int take_forks(t_philo_data *philo_data, long long start_time)
{
	pthread_mutex_lock(&philo_data->fork_r->fork);
	philo_data->fork_r->is_in_use = true;
	if (get_died(philo_data->dining))
			return (false);
	printf("%lli %u has taken a fork\n", get_time(start_time), philo_data->id);
	pthread_mutex_lock(&philo_data->fork_l->fork);
	philo_data->fork_l->is_in_use = true;
	if (get_died(philo_data->dining))
			return (false);
	printf("%lli %u has taken a fork\n", get_time(start_time), philo_data->id);
	return (true);
}

void leave_forks(t_philo_data *philo_data)
{
	time_to_act(philo_data->dining->time_to_eat);
	philo_data->fork_r->is_in_use = false;
	pthread_mutex_unlock(&philo_data->fork_r->fork);
	philo_data->fork_l->is_in_use = false;
	pthread_mutex_unlock(&philo_data->fork_l->fork);
}
