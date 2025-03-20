/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:27:03 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/19 23:41:26 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_dining_data	*dining;
	pthread_t		*philos;
	int				i;

	dining = malloc(sizeof(t_dining_data));
	if (!dining)
		return (0);
	if (input_parser(ac, av, dining) == INVALID_INPUT)
	{
		return(input_error("Invalid arguments"));
	}
	if (!set_mutexes(dining))
	{
		free(dining);
		return(0);
	}
	dining->sync_n = 0;
	dining->is_enough = false;
	dining->forks = get_forks(dining->number_of_philos);
	dining->start_time = get_time(0);
	philos = get_philos(dining->number_of_philos, dining);
	i = 0;
	while (i < (int)dining->number_of_philos)
		pthread_join(philos[i++], NULL);
	return(0);
}
