/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_20250312003237.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:27:03 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/21 08:57:19 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//a.out 5 800 200 200 [5]
//a.out philos die eat sleep [meals]

#include "philo.h"

pthread_t	*init_philos(int n_of_philos, pthread_mutex_t *forks)
{
	pthread_t		*philos;
	t_philo_data	*philo_data;
	int				i;

	i = 0;
	philos = malloc(sizeof(pthread_t) * n_of_philos);
	philo_data = malloc(sizeof(t_philo_data) * n_of_philos);

	while (i < n_of_philos)
	{
		philo_data[i].id = i;
		philo_data[i].fork_r = &forks[i];
		if (i == n_of_philos - 1)
			philo_data[i].fork_l = &forks[0];
		else
			philo_data[i].fork_l = &forks[i + 1];
		pthread_create(philos, NULL, philo_routine, (void *)&philo_data[i]);
		i++;
	}

	return (philos);
}

int main(int ac, char **av)
{
	t_dining_data	*dining;

	if (input_parser(ac, av, dining) == INVALID_INPUT)
	{
		return(input_error("Invalid arguments"));
	}
	return(0);
}
