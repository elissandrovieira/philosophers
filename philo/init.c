/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:01:27 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/21 09:06:57 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *philo_routine(void *arg)
{
	t_philo_data *philo_data;
	long long start_time;

	philo_data = (t_philo_data *)arg;
	pthread_mutex_lock(&philo_data->dining->sync);
	philo_data->dining->sync_n++;
	pthread_mutex_unlock(&philo_data->dining->sync);
	while (philo_data->dining->sync_n != (int)philo_data->dining->number_of_philos)
	{
		usleep(0);
	}
	start_time = philo_data->dining->start_time;
	if ((philo_data->id % 2) == 0)
		time_to_act(philo_data->dining->time_to_eat);
	run_dining(philo_data, start_time);
	return (NULL);
}

static t_fork *init_forks(int n_of_forks)
{
	t_fork *forks;
	int i;

	i = 0;
	if (n_of_forks == 1)
		n_of_forks = 2;
	forks = malloc(sizeof(t_fork) * n_of_forks);
	while (i < n_of_forks)
	{
		if (pthread_mutex_init(&forks[i].fork, NULL) != 0
			|| pthread_mutex_init(&forks[i].is_in_use_m, NULL) != 0)
		{
			while (i)
			{
				pthread_mutex_destroy(&forks[i].fork);
				pthread_mutex_destroy(&forks[i].is_in_use_m);
				i--;
			}
			free(forks);
			return (NULL);
		};
		forks->is_in_use = 0;
		i++;
	}
	return (forks);
}

t_dining_data	*init_dining(int ac, char **av)
{
	t_dining_data	*dining;

	dining = malloc(sizeof(t_dining_data));
	if (input_parser(ac, av, dining) == INVALID_INPUT)
	{
		input_error("Invalid arguments");
		return(NULL);
	}
	dining->sync_n = 0;
	dining->is_enough = false;
	dining->forks = init_forks(dining->number_of_philos);
	dining->start_time = get_time(0);
	return (dining);
}

int	init_mutexes(t_dining_data *dining)
{
	if (pthread_mutex_init(&dining->sync, NULL) != 0
		|| pthread_mutex_init(&dining->is_enough_m, NULL) != 0
		|| pthread_mutex_init(&dining->print_m, NULL) != 0
	)
	{
		pthread_mutex_destroy(&dining->sync);
		pthread_mutex_destroy(&dining->is_enough_m);
		pthread_mutex_destroy(&dining->print_m);
		return (false);
	};
	return (true);
}
pthread_t *init_philos(int n_of_philos, t_dining_data *dining)
{
	pthread_t *philos;
	t_philo_data *philo_data;
	int i;

	i = 0;
	philos = malloc(sizeof(pthread_t) * n_of_philos);
	philo_data = malloc(sizeof(t_philo_data) * n_of_philos);
	while (i < n_of_philos)
	{
		philo_data[i].id = i + 1;
		philo_data[i].dining = dining;
		philo_data[i].fork_r = &dining->forks[i];
		philo_data[i].last_meal_time = 0;
		philo_data[i].last_meal_n = 0;
		if (i == n_of_philos - 1 && n_of_philos != 1)
			philo_data[i].fork_l = &dining->forks[0];
		else
			philo_data[i].fork_l = &dining->forks[i + 1];
		pthread_create(&philos[i], NULL, philo_routine, (void *)&philo_data[i]);
		i++;
	}

	return (philos);
}
