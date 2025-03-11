/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:41:37 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/11 12:26:23 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philo_routine(void *arg)
{
	t_data		*philo_data;
	int			is_unlocked;

	philo_data = (t_data *)arg;
	is_unlocked = 0;
	if((philo_data->id % 2) == 0)
	{
		pthread_mutex_lock(&philo_data->fork_r);
		if (pthread_mutex_lock(&philo_data->fork_l) != 0)
		{
			pthread_mutex_unlock(&philo_data->fork_r);
			is_unlocked = 1;
		}
		usleep(10000);
		printf("%u | rangando\n", philo_data->id);
		pthread_mutex_unlock(&philo_data->fork_r);
		pthread_mutex_unlock(&philo_data->fork_l);
	}
	else
	{

		pthread_mutex_lock(&philo_data->fork_l);
		pthread_mutex_lock(&philo_data->fork_r);
		usleep(10000);
		printf("%u | rangando\n", philo_data->id);
		pthread_mutex_unlock(&philo_data->fork_l);
		pthread_mutex_unlock(&philo_data->fork_r);
	}
	return(NULL);
}

pthread_mutex_t *get_forks(int n_of_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * n_of_forks);
	while(i < n_of_forks)
	{
		if (pthread_mutex_init(&forks[i++], NULL) != 0)
		{
			write(1, "Error\n", 6);
			while (i)
				pthread_mutex_destroy(&forks[i--]);
			free(forks);
			return (NULL);
		};
	}
	return (forks);
}

pthread_t	*get_philos(int n_of_philos, pthread_mutex_t *forks)
{
	pthread_t	*init_philos;
	t_data		*philo_data;
	int			i;

	i = 0;
	init_philos = malloc(sizeof(pthread_t) * n_of_philos);
	philo_data = malloc(sizeof(t_data) * n_of_philos);

	while (i < n_of_philos)
	{
		philo_data[i].id = i;
		philo_data[i].fork_r = forks[i];
		if (i == n_of_philos - 1)
			philo_data[i].fork_l = forks[0];
		else
			philo_data[i].fork_l = forks[i + 1];
		pthread_create(init_philos, NULL, philo_routine, (void *)&philo_data[i]);
		i++;
	}

	return (init_philos);
}

//a.out 5 200 200 100 [5]

int	main(int ac, char **av)
{
	pthread_mutex_t *forks;
	pthread_t		*philos;
	int				n_of_philos;
	int				i;

	if (ac != 5 || ac != 6)
	{
		input_error("Invalid inputs");
		return (INPUT_ERROR);
	}

	n_of_philos = ft_atoi(av[1]);
	forks = get_forks(n_of_philos);
	philos = get_philos(n_of_philos, forks);
	i = 0;
	while (i < n_of_philos)
		pthread_join(philos[i++], NULL);

	return (0);

}
