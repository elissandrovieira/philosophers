/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:27:03 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/22 15:02:38 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutexes(t_dining_data *dining)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_destroy(&dining->sync_m);
	pthread_mutex_destroy(&dining->is_enough_m);
	pthread_mutex_destroy(&dining->print);
	while (i < dining->number_of_philos)
		pthread_mutex_destroy(&dining->forks[i++].fork);
}

int	main(int ac, char **av)
{
	t_dining_data	*dining;
	pthread_t		*philos;
	int				i;

	dining = init_dining(ac, av);
	if (!dining)
		return (0);
	if (!init_mutexes(dining))
	{
		free(dining);
		return (0);
	}
	philos = init_philos(dining);
	i = 0;
	while (i < (int)dining->number_of_philos)
		pthread_join(philos[i++], NULL);
	destroy_mutexes(dining);
	return (0);
}
