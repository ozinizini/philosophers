/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:24:53 by ozini             #+#    #+#             */
/*   Updated: 2024/06/01 13:41:39 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eating(t_philosopher *philo)
{
	long	timestamp;

	timestamp = get_relative_milliseconds(philo->meal->data->initial_time);
	printf("%d %d is eating\n", timestamp, philo->philo_index);
	while (timestamp < philo->meal->data->time_to_eat)
	{
		timestamp = get_relative_milliseconds(philo->meal->data->initial_time);
	}
}

void	philo_sleeping(t_philosopher *philo)
{
	long	timestamp;

	timestamp = get_relative_milliseconds(philo->meal->data->initial_time);
	printf("%d %d is sleeping\n", timestamp, philo->philo_index);
	while (timestamp < philo->meal->data->time_to_sleep)
	{
		timestamp = get_relative_milliseconds(philo->meal->data->initial_time);
	}
}

void	philo_thinking(t_philosopher *philo)
{
	long	timestamp;

	timestamp = get_relative_milliseconds(philo->meal->data->initial_time);
	printf("%d %d is thinking\n", timestamp, philo->philo_index);
}

