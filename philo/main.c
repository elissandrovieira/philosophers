/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:41:37 by eteofilo          #+#    #+#             */
/*   Updated: 2025/02/23 14:17:55 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void *philo_routine(void *arg)
{
	pthread_t		id;
	t_forks		*forks;

	id = pthread_self();
	forks = (t_forks *)arg;
	if((id % 2) == 0)
	{
		pthread_mutex_lock(&forks->right);
		pthread_mutex_lock(&forks->left);
		usleep(10000);
		printf("%lu | rangando\n", id);
		pthread_mutex_unlock(&forks->right);
		pthread_mutex_unlock(&forks->left);
	}
	else
	{

		pthread_mutex_lock(&forks->left);
		pthread_mutex_lock(&forks->right);
		usleep(10000);
		printf("%lu | rangando\n", id);
		pthread_mutex_unlock(&forks->left);
		pthread_mutex_unlock(&forks->right);
	}
	return(NULL);
}

pthread_mutex_t *get_forks(int n_of_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * n_of_forks);
	while(i < n_of_forks)
	{
		if (pthread_mutex_init(&forks[i++], NULL) != 0)
		{
			write(1, "Error\n", 6);
			while (i)
				pthread_mutex_destroy(&forks[i--]);
			free(forks);
			return (NULL);
		};
	}
	return (forks);
}

pthread_t	*get_philos(int n_of_philos, pthread_mutex_t *forks)
{
	pthread_t	*init_philos;
	t_forks		*personal_forks;
	int			i;

	i = 0;
	init_philos = malloc(sizeof(pthread_t) * n_of_philos);
	personal_forks = malloc(sizeof(t_forks) * n_of_philos);
	while (i < n_of_philos)
	{
		personal_forks[i].right = forks[i];
		if (i == n_of_philos - 1)
			personal_forks[i].left = forks[0];
		else
			personal_forks[i].left = forks[i + 1];
		pthread_create(init_philos, NULL, philo_routine, (void *)&personal_forks[i]);
		i++;
	}

	return (init_philos);
}

int	main(int ac, char **av)
{
	pthread_mutex_t *forks;
	pthread_t		*philos;
	int				n_of_philos;
	int				i;

	(void)ac;

	n_of_philos = ft_atoi(av[1]);
	forks = get_forks(n_of_philos);
	philos = get_philos(n_of_philos, forks);
	i = 0;
	while (i < n_of_philos)
		pthread_join(philos[i++], NULL);

	return (0);

}
