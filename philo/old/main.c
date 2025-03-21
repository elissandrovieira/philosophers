/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:27:03 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/21 08:57:19 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_dining_data	*init_dining(int ac, char **av)
{
	t_dining_data	*dining;

	dining = malloc(sizeof(t_dining_data));
	if (!dining)
		return (NULL);
	if (input_parser(ac, av, dining) == INVALID_INPUT)
	{
		input_error("Invalid arguments");
		return(NULL);
	}
	dining->sync = 0;
	dining->is_enough = FALSE;
	dining->forks = get_forks(dining->number_of_philos);
	dining->start_time = get_time(0);
	return (dining);
}

static int	init_mutexes(t_dining_data *dining)
{
	if (pthread_mutex_init(&dining->sync_m, NULL) != 0
		|| pthread_mutex_init(&dining->is_enough_m, NULL) != 0
		|| pthread_mutex_init(&dining->print, NULL) != 0
	)
	{
		write(1, "Error\n", 6);
			pthread_mutex_destroy(&dining->sync_m);
			pthread_mutex_destroy(&dining->is_enough_m);
			pthread_mutex_destroy(&dining->print);
		return (FALSE);
	};
	return (TRUE);
}

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
		return(0);
	}
	philos = init_philos(dining->number_of_philos, dining);
	i = 0;
	while (i < (int)dining->number_of_philos)
		pthread_join(philos[i++], NULL);
	destroy_mutexes(dining);
	return(0);
}
