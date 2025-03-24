/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:46:32 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/24 15:30:47 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutex_order	mutex_order(t_fork *first, t_fork *second)
{
	t_mutex_order	in_use;
	t_fork	*temp;

	in_use.first = first;
	in_use.second = second;
	if (&in_use.first->fork > &in_use.second->fork)
	{
		temp = in_use.first;
		in_use.first = in_use.second;
		in_use.second = temp;
	}
	return (in_use);
}

// static int	take_a_fork(t_philo_data *philo_data, t_fork *fork, long long start_time)
// {
// 	//printf("id: %i | Entrei aqui\n", philo_data->id);
// 	pthread_mutex_lock(&fork->fork);
// 	pthread_mutex_lock(&fork->is_in_use_m);
// 	fork->is_in_use = TRUE;
// 	pthread_mutex_unlock(&fork->is_in_use_m);
// 	if (get_died(philo_data->dining))
// 		return (FALSE);
// 	print_message(philo_data, start_time, "has taken a fork");
// 	return (TRUE);
// }

int	take_forks(t_philo_data *philo_data, long long start_time)
{
	t_mutex_order	forks;

	forks = mutex_order(philo_data->fork_l, philo_data->fork_r);
	pthread_mutex_lock(&forks.first->fork);
	pthread_mutex_lock(&forks.first->is_in_use_m);
	forks.first->is_in_use = TRUE;
	pthread_mutex_unlock(&forks.first->is_in_use_m);
	if (get_died(philo_data->dining))
		return (FALSE);
	print_message(philo_data, start_time, "has taken a fork");
	forks = mutex_order(philo_data->fork_l, philo_data->fork_r);
	pthread_mutex_lock(&forks.second->fork);
	pthread_mutex_lock(&forks.second->is_in_use_m);
	forks.second->is_in_use = TRUE;
	pthread_mutex_unlock(&forks.second->is_in_use_m);
	if (get_died(philo_data->dining))
		return (FALSE);
	print_message(philo_data, start_time, "has taken a fork");
	return (TRUE);
}

void	leave_forks(t_philo_data *philo_data)
{
	t_mutex_order	forks;

	forks = mutex_order(philo_data->fork_l, philo_data->fork_r);
	pthread_mutex_lock(&forks.first->is_in_use_m);
	pthread_mutex_lock(&forks.second->is_in_use_m);
	philo_data->fork_r->is_in_use = FALSE;
	philo_data->fork_l->is_in_use = FALSE;
	pthread_mutex_unlock(&forks.first->fork);
	pthread_mutex_unlock(&forks.second->fork);
	pthread_mutex_unlock(&forks.first->is_in_use_m);
	pthread_mutex_unlock(&forks.second->is_in_use_m);
}
