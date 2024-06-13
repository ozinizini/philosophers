/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:13:01 by ozini             #+#    #+#             */
/*   Updated: 2024/06/13 13:34:45 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	read_philos_ready(t_meal *meal)
{
	int	philos_ready;

	pthread_mutex_lock(&meal->philos_ready_mutex);
	philos_ready = meal->philos_ready;
	pthread_mutex_unlock(&meal->philos_ready_mutex);
	return (philos_ready);
}

void	set_philos_ready(t_meal *meal)
{
	pthread_mutex_lock(&meal->philos_ready_mutex);
	meal->philos_ready = 1;
	pthread_mutex_unlock(&meal->philos_ready_mutex);
}

long	read_initial_time(t_meal *meal)
{
	long	initial_time;

	pthread_mutex_lock(&meal->init_time_mutex);
	initial_time = meal->initial_time;
	pthread_mutex_unlock(&meal->init_time_mutex);
	return (initial_time);
}

void	set_initial_time(t_meal *meal)
{
	pthread_mutex_lock(&meal->init_time_mutex);
	meal->initial_time = get_absolute_milliseconds();
	pthread_mutex_unlock(&meal->init_time_mutex);
}
