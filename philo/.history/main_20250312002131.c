/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:27:03 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/12 00:21:31 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//a.out 5 800 200 200 [5]
//a.out philos die eat sleep [meals]

#include "philo.h"

int main(int ac, char **av)
{
	t_dining_data	*dining;

	if (input_parser(ac, av, dining) == INVALID_INPUT)
	{
		return(input_error("Invalid arguments"));
	}

	printf("philos: %u\ndie: %u\neat: %u\nsleep: %u\nmeals: %i\n", dining->number_of_philos, dining->time_to_die, dining->time_to_eat, dining->time_to_sleep, dining->number_of_meals);
	return(0);
}
