/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:40:52 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/24 19:54:54 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_died(t_philo_data *philo_data, long long start_time)
{
	int	time_to_die;

	pthread_mutex_lock(&philo_data->dining->time_to_die_m);
	time_to_die = philo_data->dining->time_to_die;
	pthread_mutex_unlock(&philo_data->dining->time_to_die_m);
	if (philo_data->last_meal_time != 0
		&& get_time(philo_data->last_meal_time) > time_to_die)
	{
		print_message(philo_data, start_time, "died");
		pthread_mutex_lock(&philo_data->dining->is_enough_m);
		philo_data->dining->is_enough = TRUE;
		pthread_mutex_unlock(&philo_data->dining->is_enough_m);
		return (TRUE);
	}
	return (FALSE);
}

int	set_thinking(t_philo_data *philo_data, long long start_time)
{
	t_mutex_order	forks;

	forks = mutex_order(philo_data->fork_l, philo_data->fork_r);
	if (!forks.first || !forks.second)
		return (FALSE);
	pthread_mutex_lock(&forks.first->is_in_use_m);
	pthread_mutex_lock(&forks.second->is_in_use_m);
	if (forks.first->is_in_use == TRUE
		|| forks.second->is_in_use == TRUE)
	{
		pthread_mutex_unlock(&forks.second->is_in_use_m);
		pthread_mutex_unlock(&forks.first->is_in_use_m);
		if (get_died(philo_data->dining))
			return (FALSE);
		if (philo_data->thinking == FALSE)
			print_message(philo_data, start_time, "is thinking");
		else
			philo_data->thinking = FALSE;
	}
	else
	{
		pthread_mutex_unlock(&forks.second->is_in_use_m);
		pthread_mutex_unlock(&forks.first->is_in_use_m);
	}
	return (TRUE);
}

int	set_eating(t_philo_data *philo_data, long long start_time)
{
	int	time_to_eat;

	if (!take_forks(philo_data, start_time))
		return (FALSE);
	philo_data->last_meal_time = get_time(0);
	if (get_died(philo_data->dining))
		return (FALSE);
	pthread_mutex_lock(&philo_data->dining->time_to_eat_m);
	time_to_eat = philo_data->dining->time_to_eat;
	pthread_mutex_unlock(&philo_data->dining->time_to_eat_m);
	print_message(philo_data, start_time, "is eating");
	time_to_act(time_to_eat);
	leave_forks(philo_data);
	return (TRUE);
}

int	set_sleeping(t_philo_data *philo_data, long long start_time)
{
	int	time_to_sleep;

	if (get_died(philo_data->dining))
		return (FALSE);
	pthread_mutex_lock(&philo_data->dining->time_to_sleep_m);
	time_to_sleep = philo_data->dining->time_to_sleep;
	pthread_mutex_unlock(&philo_data->dining->time_to_sleep_m);
	print_message(philo_data, start_time, "is sleeping");
	time_to_act(time_to_sleep);
	return (TRUE);
}
