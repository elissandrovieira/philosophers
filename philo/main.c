/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:27:03 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/24 18:43:59 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_dining_data	*dining;
	t_thread_list	*threads;
	int				i;

	dining = init_dining(ac, av);
	if (!dining)
		return (0);
	if (!init_mutexes(dining))
	{
		free(dining);
		return (0);
	}
	threads = init_philos(dining);
	i = 0;
	pthread_join(*threads->monitor, NULL);
	while (i < (int)dining->number_of_philos)
		pthread_join(threads->philos[i++], NULL);
	destroy_mutexes(dining);
	destroy_allocs(dining, threads);
	return (0);
}
