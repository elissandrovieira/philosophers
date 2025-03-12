/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:36:01 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/12 00:23:06 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	signal;

	if (!nptr)
		return (INVALID_INPUT);
	i = 0;
	n = 0;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		n = (n * 10) + nptr[i] - 48;
		i++;
	}
	if(nptr[i] != '\0')
		return (INVALID_INPUT);
	return (n * signal);
}

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
	else
		dining->number_of_meals = INVALID_INPUT;

	printf("philos: %u\ndie: %u\neat: %u\nsleep: %u\nmeals: %i\n", dining->number_of_philos, dining->time_to_die, dining->time_to_eat, dining->time_to_sleep, dining->number_of_meals);
	if (
		ac == 6 && dining->number_of_meals == INVALID_INPUT
		|| dining->number_of_philos == INVALID_INPUT
		|| dining->time_to_die == INVALID_INPUT
		|| dining->time_to_eat == INVALID_INPUT
		|| dining->time_to_sleep == INVALID_INPUT
	)
		return (INVALID_INPUT);
	return (0);
}
