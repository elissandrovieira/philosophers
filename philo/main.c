/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:27:03 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/20 19:13:59 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int				init_mutexes(t_dining_data *dining);
static t_dining_data	*init_dining(void);

int	main(int ac, char **av)
{
	t_dining_data	*dining;
	pthread_t		*philos;
	int				i;

	dining = init_dining();
	if (!dining)
		return (0);
	if (input_parser(ac, av, dining) == INVALID_INPUT)
		return (input_error("Invalid arguments"));
	if (!init_mutexes(dining))
	{
		free(dining);
		return (FALSE);
	}
	philos = get_philos(dining);
	i = 0;
	while (i < (int)dining->number_of_philos)
		pthread_join(philos[i++], NULL);
	return (0);
}

static int	init_mutexes(t_dining_data *dining)
{
	if (pthread_mutex_init(&dining->sync, NULL) != 0
		|| pthread_mutex_init(&dining->get_enough, NULL) != 0)
	{
		write(1, "Error\n", 6);
		pthread_mutex_destroy(&dining->sync);
		pthread_mutex_destroy(&dining->get_enough);
		return (FALSE);
	}
	return (TRUE);
}

static t_dining_data	*init_dining(void)
{
	t_dining_data	*dining;

	dining = malloc(sizeof(t_dining_data));
	if (!dining)
		return (NULL);
	dining->sync_n = 0;
	dining->is_enough = FALSE;
	dining->forks = get_forks(dining->number_of_philos);
	dining->start_time = get_time(0);
	return (dining);
}
