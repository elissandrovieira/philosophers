/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteofilo <eteofilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 05:45:44 by eteofilo          #+#    #+#             */
/*   Updated: 2025/03/11 11:39:32 by eteofilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define INPUT_ERROR 1

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_data
{
	pthread_mutex_t	lock_forks;
	unsigned int	id;
	unsigned int	*fork_r;
	unsigned int	*fork_l;
}	t_data;

int	ft_atoi(const char *nptr);


#endif
