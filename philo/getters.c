/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:49:28 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/24 18:22:36 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_died(t_dining_data *dining)
{
	pthread_mutex_lock(&dining->is_enough_m);
	if (dining->is_enough == TRUE)
	{
		pthread_mutex_unlock(&dining->is_enough_m);
		return (TRUE);
	}
	pthread_mutex_unlock(&dining->is_enough_m);
	return (FALSE);
}

long long	get_time(long long start_time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (((tv.tv_sec * (long long)1000) + (tv.tv_usec / 1000)) - start_time);
}
