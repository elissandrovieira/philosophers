/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:46:32 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/22 15:56:55 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutex_order	mutex_order(pthread_mutex_t *first, pthread_mutex_t *second)
{
	t_mutex_order	in_use;
	pthread_mutex_t	*temp;

	in_use.first = first;
	in_use.second = second;
	if (in_use.first > in_use.second)
	{
		temp = in_use.first;
		in_use.first = in_use.second;
		in_use.second = temp;
	}
	return (in_use);
}

int	take_forks(t_philo_data *philo_data, long long start_time)
{
	t_mutex_order	is_in_use_m;
	t_mutex_order	forks;

	is_in_use_m = mutex_order(&philo_data->fork_l->is_in_use_m,
			&philo_data->fork_r->is_in_use_m);
	forks = mutex_order(&philo_data->fork_l->fork, &philo_data->fork_r->fork);
	pthread_mutex_lock(forks.first);
	pthread_mutex_lock(is_in_use_m.first);
	philo_data->fork_r->is_in_use = TRUE;
	pthread_mutex_unlock(is_in_use_m.first);
	if (get_died(philo_data->dining))
		return (FALSE);
	print_message(philo_data, start_time, "has taken a fork");
	pthread_mutex_lock(forks.second);
	pthread_mutex_lock(is_in_use_m.second);
	philo_data->fork_l->is_in_use = TRUE;
	pthread_mutex_unlock(is_in_use_m.second);
	if (get_died(philo_data->dining))
		return (FALSE);
	print_message(philo_data, start_time, "has taken a fork");
	return (TRUE);
}

void	leave_forks(t_philo_data *philo_data)
{
	t_mutex_order	is_in_use_m;
	t_mutex_order	forks;

	is_in_use_m = mutex_order(&philo_data->fork_l->is_in_use_m,
			&philo_data->fork_r->is_in_use_m);
	forks = mutex_order(&philo_data->fork_l->fork, &philo_data->fork_r->fork);
	pthread_mutex_lock(&philo_data->dining->time_to_eat_m);
	time_to_act(philo_data->dining->time_to_eat);
	pthread_mutex_unlock(&philo_data->dining->time_to_eat_m);
	pthread_mutex_lock(is_in_use_m.first);
	pthread_mutex_lock(is_in_use_m.second);
	philo_data->fork_r->is_in_use = FALSE;
	philo_data->fork_l->is_in_use = FALSE;
	pthread_mutex_unlock(forks.first);
	pthread_mutex_unlock(forks.second);
	pthread_mutex_unlock(is_in_use_m.second);
	pthread_mutex_unlock(is_in_use_m.first);
}
