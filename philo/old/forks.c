/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:46:32 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/21 06:26:53 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int take_forks(t_philo_data *philo_data, long long start_time)
{
	// if (philo_data->id % 2 == 0)
	// {
	// 	pthread_mutex_lock(&philo_data->fork_l->fork);
	// 	pthread_mutex_lock(&philo_data->fork_l->is_in_use_m);
	// 	philo_data->fork_l->is_in_use = TRUE;
	// 	pthread_mutex_unlock(&philo_data->fork_l->is_in_use_m);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&philo_data->fork_r->fork);
	// 	pthread_mutex_lock(&philo_data->fork_r->is_in_use_m);
	// 	philo_data->fork_r->is_in_use = TRUE;
	// 	pthread_mutex_unlock(&philo_data->fork_r->is_in_use_m);
	// }
	pthread_mutex_lock(&philo_data->fork_l->fork);
	pthread_mutex_lock(&philo_data->fork_l->is_in_use_m);
	philo_data->fork_l->is_in_use = TRUE;
	pthread_mutex_unlock(&philo_data->fork_l->is_in_use_m);
	if (get_died(philo_data->dining))
			return (FALSE);
	pthread_mutex_lock(&philo_data->dining->print);
	printf("%lli %u has taken a fork\n", get_time(start_time), philo_data->id);
	pthread_mutex_unlock(&philo_data->dining->print);
	// if (philo_data->id % 2 == 0)
	// {
	// 	pthread_mutex_lock(&philo_data->fork_r->fork);
	// 	pthread_mutex_lock(&philo_data->fork_r->is_in_use_m);
	// 	philo_data->fork_r->is_in_use = TRUE;
	// 	pthread_mutex_unlock(&philo_data->fork_r->is_in_use_m);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&philo_data->fork_l->fork);
	// 	pthread_mutex_lock(&philo_data->fork_l->is_in_use_m);
	// 	philo_data->fork_l->is_in_use = TRUE;
	// 	pthread_mutex_unlock(&philo_data->fork_l->is_in_use_m);
	// }
	pthread_mutex_lock(&philo_data->fork_r->fork);
	pthread_mutex_lock(&philo_data->fork_r->is_in_use_m);
	philo_data->fork_r->is_in_use = TRUE;
	pthread_mutex_unlock(&philo_data->fork_r->is_in_use_m);
	if (get_died(philo_data->dining))
			return (FALSE);
	pthread_mutex_lock(&philo_data->dining->print);
	printf("%lli %u has taken a fork\n", get_time(start_time), philo_data->id);
	pthread_mutex_unlock(&philo_data->dining->print);
	return (TRUE);
}

void leave_forks(t_philo_data *philo_data)
{
	time_to_act(philo_data->dining->time_to_eat);
	pthread_mutex_lock(&philo_data->fork_r->is_in_use_m);
	philo_data->fork_r->is_in_use = FALSE;
	pthread_mutex_unlock(&philo_data->fork_r->is_in_use_m);
	pthread_mutex_unlock(&philo_data->fork_r->fork);
	pthread_mutex_lock(&philo_data->fork_l->is_in_use_m);
	philo_data->fork_l->is_in_use = FALSE;
	pthread_mutex_unlock(&philo_data->fork_l->is_in_use_m);
	pthread_mutex_unlock(&philo_data->fork_l->fork);
}
