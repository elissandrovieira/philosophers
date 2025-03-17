/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:36:01 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/17 19:50:04 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;

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
	return (n);
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

long long	get_time(long long start_time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (((tv.tv_sec * (long long)1000) + (tv.tv_usec / 1000)) - start_time);
}

void	time_to_act(int action)
{
	long long end_time = get_time(0) + action;
	while (get_time(0) < end_time)
		usleep(100);
}

int	init_mutexes(t_dining_data *dining)
{
	if (pthread_mutex_init(&dining->sync, NULL) != 0
		|| pthread_mutex_init(&dining->get_enough, NULL) != 0
	)
	{
		write(1, "Error\n", 6);
			pthread_mutex_destroy(&dining->sync);
			pthread_mutex_destroy(&dining->get_enough);
		return (false);
	};
	return (true);
}

int	is_died(t_dining_data *dining)
{
	pthread_mutex_lock(&dining->get_enough);
	if (dining->is_enough == true)
	{
		pthread_mutex_unlock(&dining->get_enough);
		return (true);
	}
	pthread_mutex_unlock(&dining->get_enough);
	return (false);
}
