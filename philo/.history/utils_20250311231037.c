/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:36:01 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/11 23:10:37 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	signal;

	if (!nptr)
		return (0);
	i = 0;
	n = 0;
	signal = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signal = -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		n = (n * 10) + nptr[i] - 48;
		i++;
	}
	return (n * signal);
}

int input_error(char *string)
{
	printf("%s[ERROR]%s %s!\n", RED, RESET, string);
	printf("├ %sCorrect usage:%s ./philo n_of_philo time_to_die time_to_eat time_to_sleep %s[meals_number] <- Optional argument\n", GREEN, RESET, BLUE);
	printf("└ %sExample:%s ./philo 5 800 200 200 5\n", GREEN, RESET);
	return (INPUT_ERROR);
}
