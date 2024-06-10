/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:57:20 by ozini             #+#    #+#             */
/*   Updated: 2024/06/10 15:10:17 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	read_eating_time(t_philosopher *philo)
{
	long	eating_timestamp;

	pthread_mutex_lock(&philo->eating_time_mutex);
	eating_timestamp = philo->eating_timestamp;
	pthread_mutex_unlock(&philo->eating_time_mutex);
	return (eating_timestamp);
}

void	set_eating_time(t_philosopher *philo, long absolute_time)
{
	pthread_mutex_lock(&philo->eating_time_mutex);
	philo->eating_timestamp = absolute_time;
	pthread_mutex_unlock(&philo->eating_time_mutex);
}

long	read_meals_eaten(t_philosopher *philo)
{
	long	meals_eaten;

	pthread_mutex_lock(&philo->meals_eaten_mutex);
	meals_eaten = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	return (meals_eaten);
}

void	increase_meals_eaten(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
}
