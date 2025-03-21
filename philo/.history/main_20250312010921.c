/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_20250312010921.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:27:03 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/21 08:57:19 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//a.out 5 800 200 200 [5]
//a.out philos die eat sleep [meals]

#include "philo.h"

void *philo_routine(void *arg)
{
	t_philo_data		*philo_data;
	int			is_unlocked;

	philo_data = (t_philo_data *)arg;
	is_unlocked = 0;
	pthread_mutex_lock(&philo_data->dining->sync_m);
	philo_data->dining->sync_m++;
	pthread_mutex_unlock(&philo_data->dining->sync_m);
	while(philo_data->dining->sync_m != philo_data->dining->number_of_philos)
	{
	}
	if((philo_data->id % 2) != 0)
		usleep(philo_data->dining->time_to_eat / 2);
	pthread_mutex_lock(philo_data->fork_r);
	printf("timestamp_in_ms %u has taken a fork\n", philo_data->id);
	pthread_mutex_lock(philo_data->fork_l);
	printf("timestamp_in_ms %u has taken a fork\n", philo_data->id);
	printf("timestamp_in_ms %u is eating\n", philo_data->id);
	usleep(philo_data->dining->time_to_eat);
	pthread_mutex_unlock(philo_data->fork_r);
	pthread_mutex_unlock(philo_data->fork_l);
	printf("timestamp_in_ms %u is sleeping\n", philo_data->id);
	usleep(philo_data->dining->time_to_sleep);
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

pthread_t	*init_philos(int n_of_philos, t_dining_data *dining)
{
	pthread_t		*philos;
	t_philo_data	*philo_data;
	int				i;

	i = 0;
	philos = malloc(sizeof(pthread_t) * n_of_philos);
	philo_data = malloc(sizeof(t_philo_data) * n_of_philos);

	while (i < n_of_philos)
	{
		philo_data[i].id = i + 1;
		philo_data[i].dining = dining;
		philo_data[i].fork_r = &dining->forks[i];
		if (i == n_of_philos - 1)
			philo_data[i].fork_l = &dining->forks[0];
		else
			philo_data[i].fork_l = &dining->forks[i + 1];
		pthread_create(philos, NULL, philo_routine, (void *)&philo_data[i]);
		i++;
	}

	return (philos);
}

int main(int ac, char **av)
{
	t_dining_data	*dining;
	pthread_t		*philos;
	int				i;

	if (input_parser(ac, av, dining) == INVALID_INPUT)
	{
		return(input_error("Invalid arguments"));
	}
	dining->sync_m = 0;
	dining->forks = get_forks(dining->number_of_philos);
	philos = init_philos(dining->number_of_philos, dining);
	i = 0;
	while (i < dining->number_of_philos)
		pthread_join(philos[i++], NULL);
	return(0);
}
