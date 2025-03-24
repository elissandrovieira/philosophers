/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:40:52 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/22 16:04:30 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_died(t_philo_data *philo_data, long long start_time)
{
	pthread_mutex_lock(&philo_data->dining->time_to_die_m);
	if (philo_data->last_meal_time != 0 && get_time(philo_data->last_meal_time)
		> philo_data->dining->time_to_die)
	{
		pthread_mutex_unlock(&philo_data->dining->time_to_die_m);
		print_message(philo_data, start_time, "died");
		pthread_mutex_lock(&philo_data->dining->is_enough_m);
		philo_data->dining->is_enough = TRUE;
		pthread_mutex_unlock(&philo_data->dining->is_enough_m);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo_data->dining->time_to_die_m);
	return (FALSE);
}

int	set_thinking(t_philo_data *philo_data, long long start_time)
{
	t_mutex_order	is_in_use_m;

	is_in_use_m = mutex_order(&philo_data->fork_l->is_in_use_m,
			&philo_data->fork_r->is_in_use_m);
	pthread_mutex_lock(is_in_use_m.first);
	pthread_mutex_lock(is_in_use_m.second);
	if (philo_data->fork_l->is_in_use == TRUE
		|| philo_data->fork_r->is_in_use == TRUE)
	{
		pthread_mutex_unlock(is_in_use_m.second);
		pthread_mutex_unlock(is_in_use_m.first);
		if (get_died(philo_data->dining))
			return (FALSE);
		pthread_mutex_lock(&philo_data->dining->print);
		printf("%lli %u is thinking\n", get_time(start_time), philo_data->id);
		pthread_mutex_unlock(&philo_data->dining->print);
	}
	else
	{
		pthread_mutex_unlock(is_in_use_m.second);
		pthread_mutex_unlock(is_in_use_m.first);
	}
	return (TRUE);
}

int	set_eating(t_philo_data *philo_data, long long start_time)
{
	if (!take_forks(philo_data, start_time))
		return (FALSE);
	philo_data->last_meal_time = get_time(0);
	if (get_died(philo_data->dining))
		return (FALSE);
	pthread_mutex_lock(&philo_data->dining->print);
	printf("%lli %u is eating\n", get_time(start_time), philo_data->id);
	pthread_mutex_unlock(&philo_data->dining->print);
	leave_forks(philo_data);
	return (TRUE);
}

int	set_sleeping(t_philo_data *philo_data, long long start_time)
{
	if (get_died(philo_data->dining))
		return (FALSE);
	pthread_mutex_lock(&philo_data->dining->print);
	printf("%lli %u is sleeping\n", get_time(start_time), philo_data->id);
	pthread_mutex_unlock(&philo_data->dining->print);
	pthread_mutex_lock(&philo_data->dining->time_to_sleep_m);
	time_to_act(philo_data->dining->time_to_sleep);
	pthread_mutex_unlock(&philo_data->dining->time_to_sleep_m);
	return (TRUE);
}
