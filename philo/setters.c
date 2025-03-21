/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:40:52 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/19 22:57:40 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_mutexes(t_dining_data *dining)
{
	if (pthread_mutex_init(&dining->sync, NULL) != 0
		|| pthread_mutex_init(&dining->get_enough, NULL) != 0
	)
	{
		write(1, "Error\n", 6);
			pthread_mutex_destroy(&dining->sync);
			pthread_mutex_destroy(&dining->get_enough);
		return (false);
	};
	return (true);
}

int	set_died(t_philo_data *philo_data, long long start_time)
{
	if (philo_data->last_meal_time != 0 && get_time(philo_data->last_meal_time) > philo_data->dining->time_to_die)
	{
		printf("%lli %u died\n", get_time(start_time), philo_data->id);
		pthread_mutex_lock(&philo_data->dining->get_enough);
		philo_data->dining->is_enough = true;
		pthread_mutex_unlock(&philo_data->dining->get_enough);
		return (true);
	}
	return (false);
}

int	set_thinking(t_philo_data *philo_data, long long start_time)
{
	if (philo_data->fork_l->is_in_use == true || philo_data->fork_r->is_in_use == true)
	{
		if (get_died(philo_data->dining))
			return (false);
		printf("%lli %u is thinking\n", get_time(start_time), philo_data->id);
	}
	return (true);
}

int set_eating(t_philo_data *philo_data, long long start_time)
{
	if (!take_forks(philo_data, start_time))
		return(false);
	philo_data->last_meal_time = get_time(0);
	if (get_died(philo_data->dining))
			return (false);
	printf("%lli %u is eating\n", get_time(start_time), philo_data->id);
	leave_forks(philo_data);
	return (true);
}

int set_sleeping(t_philo_data *philo_data, long long start_time)
{
	if (get_died(philo_data->dining))
			return (false);
	printf("%lli %u is sleeping\n", get_time(start_time), philo_data->id);
	time_to_act(philo_data->dining->time_to_sleep);
	return (true);
}
