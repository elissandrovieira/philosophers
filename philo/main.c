/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:27:03 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/15 13:47:51 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//a.out 5 800 200 200 [5]
//a.out philos die eat sleep [meals]

#include "philo.h"

void *philo_routine(void *arg)
{
	t_philo_data		*philo_data;
	int			i = 0;
	long long			start_time;

	philo_data = (t_philo_data *)arg;
	pthread_mutex_lock(&philo_data->dining->sync);
	philo_data->dining->sync_n++;
	pthread_mutex_unlock(&philo_data->dining->sync);
	while(philo_data->dining->sync_n != (int)philo_data->dining->number_of_philos)
	{
		usleep(0);
	}
	start_time = philo_data->dining->start_time;
	if((philo_data->id % 2) != 0)
		usleep(philo_data->dining->time_to_eat / 2);
	while (i < 5)
	{
		if (philo_data->last_meal_time != 0 && get_time(philo_data->last_meal_time) > philo_data->dining->time_to_die)
		{
			//printf("%u last_meal_time: %lli\n", philo_data->id, get_time() - philo_data->last_meal_time);
			printf("%lli %u die\n", get_time(start_time), philo_data->id);
			break;
		}
		if (philo_data->fork_l->is_in_use == true || philo_data->fork_r->is_in_use == true)
			printf("%lli %u is thinking\n", get_time(start_time), philo_data->id);
		pthread_mutex_lock(&philo_data->fork_r->fork);
		philo_data->fork_r->is_in_use = true;
		printf("%lli %u has taken a fork\n", get_time(start_time), philo_data->id);
		pthread_mutex_lock(&philo_data->fork_l->fork);
		philo_data->fork_l->is_in_use = true;
		printf("%lli %u has taken a fork\n", get_time(start_time), philo_data->id);
		philo_data->last_meal_time = get_time(0);
		printf("%lli %u is eating\n", get_time(start_time), philo_data->id);
		usleep(philo_data->dining->time_to_eat * 1000);
		philo_data->fork_r->is_in_use = false;
		pthread_mutex_unlock(&philo_data->fork_r->fork);
		philo_data->fork_l->is_in_use = false;
		pthread_mutex_unlock(&philo_data->fork_l->fork);
		printf("%lli %u is sleeping\n", get_time(start_time), philo_data->id);
		usleep(philo_data->dining->time_to_sleep * 1000);
		i++;
	}
	return(NULL);
}

t_fork *get_forks(int n_of_forks)
{
	t_fork	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(t_fork) * n_of_forks);
	while(i < n_of_forks)
	{
		if (pthread_mutex_init(&forks[i++].fork, NULL) != 0)
		{
			write(1, "Error\n", 6);
			while (i)
				pthread_mutex_destroy(&forks[i--].fork);
			free(forks);
			return (NULL);
		};
		forks->is_in_use = 0;
	}
	return (forks);
}

pthread_t	*get_philos(int n_of_philos, t_dining_data *dining)
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
		philo_data[i].last_meal_time = 0;
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

	dining = malloc(sizeof(t_dining_data));
	if (!dining)
		return (0);
	if (input_parser(ac, av, dining) == INVALID_INPUT)
	{
		return(input_error("Invalid arguments"));
	}
	dining->sync_n = 0;
	dining->forks = get_forks(dining->number_of_philos);
	dining->start_time = get_time(0);
	philos = get_philos(dining->number_of_philos, dining);
	i = 0;
	while (i < (int)dining->number_of_philos)
		pthread_join(philos[i++], NULL);
	return(0);
}
