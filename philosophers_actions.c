/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:24:53 by ozini             #+#    #+#             */
/*   Updated: 2024/06/01 14:42:07 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eating(t_philosopher *philo)
{
	long	timestamp;

	timestamp = get_relative_milliseconds(philo->meal->initial_time);

	philo->meals_eaten++;
	philo->eating_timestamp = get_absolute_milliseconds();
	pthread_mutex_lock(&philo->print_mutex);
	printf("%ld %d is eating\n", timestamp, philo->philo_index);
	pthread_mutex_unlock(&philo->print_mutex);
	while (timestamp <= philo->meal->data->time_to_eat)
	{
		if (philo->meal->finished_meal)
			break ;
		timestamp = get_relative_milliseconds(philo->meal->initial_time);
	}
}

void	philo_sleeping(t_philosopher *philo)
{
	long	timestamp;

	timestamp = get_relative_milliseconds(philo->meal->initial_time);
	pthread_mutex_lock(&philo->print_mutex);
	printf("%ld %d is sleeping\n", timestamp, philo->philo_index);
	pthread_mutex_unlock(&philo->print_mutex);
	while (timestamp <= philo->meal->data->time_to_sleep)
	{
		if (philo->meal->finished_meal)
			break ;
		timestamp = get_relative_milliseconds(philo->meal->initial_time);
	}
}

void	philo_thinking(t_philosopher *philo)
{
	long	timestamp;

	timestamp = get_relative_milliseconds(philo->meal->initial_time);
	pthread_mutex_lock(&philo->print_mutex);
	printf("%ld %d is thinking\n", timestamp, philo->philo_index);
	pthread_mutex_unlock(&philo->print_mutex);
}

