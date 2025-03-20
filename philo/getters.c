/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:49:28 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/20 19:13:14 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo_data	*philo_data;
	long long		start_time;

	philo_data = (t_philo_data *)arg;
	pthread_mutex_lock(&philo_data->dining->sync);
	philo_data->dining->sync_n++;
	pthread_mutex_unlock(&philo_data->dining->sync);
	while (philo_data->dining->sync_n
		!= (int)philo_data->dining->number_of_philos)
	{
		usleep(0);
	}
	start_time = philo_data->dining->start_time;
	if ((philo_data->id % 2) == 0)
		time_to_act(philo_data->dining->time_to_eat);
	run_dining(philo_data, start_time);
	return (NULL);
}

t_fork	*get_forks(int n_of_forks)
{
	t_fork	*forks;
	int		i;

	i = 0;
	if (n_of_forks == 1)
		n_of_forks = 2;
	forks = malloc(sizeof(t_fork) * n_of_forks);
	while (i < n_of_forks)
	{
		if (pthread_mutex_init(&forks[i++].fork, NULL) != 0)
		{
			write(1, "Error\n", 6);
			while (i)
				pthread_mutex_destroy(&forks[i--].fork);
			free(forks);
			return (NULL);
		}
		printf("fork %i\n", i);
		forks->is_in_use = 0;
	}
	return (forks);
}

pthread_t	*get_philos(t_dining_data *dining)
{
	pthread_t		*philos;
	t_philo_data	*philo_data;
	int				n_of_philos;
	int				i;

	n_of_philos = dining->number_of_philos;
	i = 0;
	philos = malloc(sizeof(pthread_t) * n_of_philos);
	philo_data = malloc(sizeof(t_philo_data) * n_of_philos);
	while (i < n_of_philos)
	{
		philo_data[i].id = i + 1;
		philo_data[i].dining = dining;
		philo_data[i].fork_r = &dining->forks[i];
		philo_data[i].last_meal_time = 0;
		if (i == n_of_philos - 1 && n_of_philos != 1)
			philo_data[i].fork_l = &dining->forks[0];
		else
			philo_data[i].fork_l = &dining->forks[i + 1];
		pthread_create(philos, NULL, philo_routine, (void *)&philo_data[i]);
		i++;
	}
	return (philos);
}

int	get_died(t_dining_data *dining)
{
	pthread_mutex_lock(&dining->get_enough);
	if (dining->is_enough == TRUE)
	{
		pthread_mutex_unlock(&dining->get_enough);
		return (TRUE);
	}
	pthread_mutex_unlock(&dining->get_enough);
	return (FALSE);
}

long long	get_time(long long start_time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (((tv.tv_sec * (long long)1000) + (tv.tv_usec / 1000)) - start_time);
}
