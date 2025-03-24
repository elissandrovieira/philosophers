/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:18:36 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/24 19:54:33 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_one(t_philo_data *philo_data, long long start_time)
{
	pthread_mutex_lock(&philo_data->fork_r->fork);
	print_message(philo_data, start_time, "has taken a fork");
	pthread_mutex_lock(&philo_data->dining->time_to_die_m);
	time_to_act(philo_data->dining->time_to_die);
	pthread_mutex_unlock(&philo_data->dining->time_to_die_m);
	print_message(philo_data, start_time, "died");
}

void	run_dining(t_philo_data *philo_data, long long start_time)
{
	int	number_of_philos;
	int	number_of_meals;
	int	i;

	i = 0;
	pthread_mutex_lock(&philo_data->dining->number_of_philos_m);
	number_of_philos = philo_data->dining->number_of_philos;
	pthread_mutex_unlock(&philo_data->dining->number_of_philos_m);
	pthread_mutex_lock(&philo_data->dining->number_of_meals_m);
	number_of_meals = philo_data->dining->number_of_meals;
	pthread_mutex_unlock(&philo_data->dining->number_of_meals_m);
	while (i != philo_data->dining->number_of_meals)
	{
		if (get_died(philo_data->dining))
			break ;
		if (!set_thinking(philo_data, start_time))
			break ;
		if (!set_eating(philo_data, start_time))
			break ;
		if (!set_sleeping(philo_data, start_time))
			break ;
		if (philo_data->dining->number_of_meals >= 0)
			i++;
	}
}

void	*philo_routine(void *arg)
{
	t_philo_data	*philo_data;
	long long		start_time;
	unsigned int	number_of_philos;

	philo_data = (t_philo_data *)arg;
	pthread_mutex_lock(&philo_data->dining->start_time_m);
	start_time = philo_data->dining->start_time;
	pthread_mutex_unlock(&philo_data->dining->start_time_m);
	pthread_mutex_lock(&philo_data->dining->number_of_philos_m);
	number_of_philos = philo_data->dining->number_of_philos;
	pthread_mutex_unlock(&philo_data->dining->number_of_philos_m);
	if (number_of_philos == 1)
	{
		handle_one(philo_data, start_time);
		return (NULL);
	}
	if ((philo_data->id % 2) == 0 || ((philo_data->id % 2) != 0
			&& philo_data->id == number_of_philos))
	{
		print_message(philo_data, start_time, "is thinking");
		time_to_act(philo_data->dining->time_to_eat / 2);
		philo_data->thinking = TRUE;
	}
	run_dining(philo_data, start_time);
	return (NULL);
}

static t_monitor_data	take_monitor_data(t_philo_data *philo_data)
{
	t_monitor_data	monitor_data;

	pthread_mutex_lock(&philo_data->dining->start_time_m);
	monitor_data.start_time = philo_data->dining->start_time;
	pthread_mutex_unlock(&philo_data->dining->start_time_m);
	pthread_mutex_lock(&philo_data->dining->number_of_philos_m);
	monitor_data.number_of_philos = philo_data->dining->number_of_philos;
	pthread_mutex_unlock(&philo_data->dining->number_of_philos_m);
	pthread_mutex_lock(&philo_data->dining->number_of_meals_m);
	monitor_data.number_of_meals = philo_data->dining->number_of_meals;
	pthread_mutex_unlock(&philo_data->dining->number_of_meals_m);
	return (monitor_data);
}

void	*monitor_routine(void *arg)
{
	t_philo_data	*philo_data;
	int				i;
	t_monitor_data	monitor_data;

	philo_data = (t_philo_data *)arg;
	monitor_data = take_monitor_data(philo_data);
	i = 0;
	while (get_died(philo_data->dining) == FALSE
		&& monitor_data.number_of_meals == INVALID_INPUT)
	{
		if (set_died(&philo_data[i], monitor_data.start_time))
			return (NULL);
		if (i + 1 == monitor_data.number_of_philos)
			i = 0;
		else
			i++;
	}
	return (NULL);
}
