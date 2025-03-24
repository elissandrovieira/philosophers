/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:53:47 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/22 15:32:52 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_dining_data	*init_dining(int ac, char **av)
{
	t_dining_data	*dining;

	dining = malloc(sizeof(t_dining_data));
	if (!dining)
		return (NULL);
	if (input_parser(ac, av, dining) == INVALID_INPUT)
	{
		input_error("Invalid arguments");
		return (NULL);
	}
	dining->sync = 0;
	dining->is_enough = FALSE;
	dining->forks = init_forks(dining->number_of_philos);
	dining->start_time = get_time(0);
	return (dining);
}

t_fork	*init_forks(int n_of_forks)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = malloc(sizeof(t_fork) * n_of_forks);
	while (i < n_of_forks)
	{
		if (pthread_mutex_init(&forks[i].fork, NULL) != 0)
		{
			while (i)
				pthread_mutex_destroy(&forks[i--].fork);
			free(forks);
			return (NULL);
		}
		forks[i].is_in_use = 0;
		i++;
	}
	return (forks);
}

int	init_mutexes(t_dining_data *dining)
{
	if (pthread_mutex_init(&dining->sync_m, NULL) != 0
		|| pthread_mutex_init(&dining->is_enough_m, NULL) != 0
		|| pthread_mutex_init(&dining->print, NULL) != 0
		|| pthread_mutex_init(&dining->number_of_meals_m, NULL) != 0
		|| pthread_mutex_init(&dining->number_of_philos_m, NULL) != 0
		|| pthread_mutex_init(&dining->start_time_m, NULL) != 0
		|| pthread_mutex_init(&dining->time_to_die_m, NULL) != 0
		|| pthread_mutex_init(&dining->time_to_eat_m, NULL) != 0
		|| pthread_mutex_init(&dining->time_to_sleep_m, NULL) != 0
	)
	{
		pthread_mutex_destroy(&dining->sync_m);
		pthread_mutex_destroy(&dining->is_enough_m);
		pthread_mutex_destroy(&dining->print);
		pthread_mutex_destroy(&dining->number_of_meals_m);
		pthread_mutex_destroy(&dining->number_of_philos_m);
		pthread_mutex_destroy(&dining->start_time_m);
		pthread_mutex_destroy(&dining->time_to_die_m);
		pthread_mutex_destroy(&dining->time_to_eat_m);
		pthread_mutex_destroy(&dining->time_to_sleep_m);
		return (FALSE);
	}
	return (TRUE);
}

pthread_t	*init_philos(t_dining_data *dining)
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
		philo_data[i].last_meal_time = 0;
		philo_data[i].fork_r = &dining->forks[i];
		if (i == n_of_philos - 1 && n_of_philos != 1)
			philo_data[i].fork_l = &dining->forks[0];
		else
			philo_data[i].fork_l = &dining->forks[i + 1];
		pthread_create(&philos[i], NULL, philo_routine, (void *)&philo_data[i]);
		i++;
	}
	return (philos);
}
