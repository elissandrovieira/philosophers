/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:08:23 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/21 08:08:40 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int input_error(char *string)
{
	printf("%s[ERROR]%s %s!\n", RED, RESET, string);
	printf("├ %sCorrect usage:%s ./philo number_of_philos time_to_die time_to_eat time_to_sleep %snumber_of_meals <- Optional argument\n%s", GREEN, RESET, BLUE, RESET);
	printf("└ %sExample:%s ./philo 5 800 200 200 5\n", GREEN, RESET);
	return (0);
}

int input_parser(int ac, char **av, t_dining_data	*dining)
{
	dining->number_of_philos = ft_atoi(av[1]);
	dining->time_to_die = ft_atoi(av[2]);
	dining->time_to_eat = ft_atoi(av[3]);
	dining->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		dining->number_of_meals = ft_atoi(av[5]);
	else if (ac == 5)
		dining->number_of_meals = INVALID_INPUT;
	if (
		(ac == 6 && dining->number_of_meals == INVALID_INPUT)
		|| ((int)dining->number_of_philos == INVALID_INPUT)
		|| ((int)dining->time_to_die == INVALID_INPUT)
		|| ((int)dining->time_to_eat == INVALID_INPUT)
		|| ((int)dining->time_to_sleep == INVALID_INPUT)
	)
		return (INVALID_INPUT);
	return (0);
}
