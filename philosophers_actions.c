/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:24:53 by ozini             #+#    #+#             */
/*   Updated: 2024/06/01 15:53:58 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	print_action(t_philo_action action_type, t_philosopher *philo)
{
	long	timestamp;

	timestamp = get_relative_milliseconds(philo->meal->initial_time);
	pthread_mutex_lock(&philo->print_mutex);
	if (action_type == EATING)
	{
		philo->eating_timestamp = timestamp;
		printf("%ld %d is eating\n", timestamp, philo->philo_index);
	}
	else if (action_type == SLEEPING)
		printf("%ld %d is sleeping\n", timestamp, philo->philo_index);
	else if (action_type == THINKING)
		printf("%ld %d is thinking\n", timestamp, philo->philo_index);
	else if (action_type == DIED)
		printf("%ld %d died\n", timestamp, philo->philo_index);
	pthread_mutex_unlock(&philo->print_mutex);
	return (timestamp);
}

void	philo_eating(t_philosopher *philo)
{
	long	timestamp;
	long	eating_elapsed_time;
	long	death_elapsed_time;

	//timestamp está relativizado a initial_time.
	timestamp = print_action(EATING, philo);
	philo->meals_eaten++;
	//Tengo que calcular el tiempo transcurrido desde timestamp
	eating_elapsed_time = get_relative_milliseconds(timestamp);
	while (eating_elapsed_time <= philo->meal->data->time_to_eat)
	{
		death_elapsed_time = get_relative_milliseconds(philo->eating_timestamp);
		if (death_elapsed_time > philo->meal->data->time_to_die)
		{
			print_action(DIED, philo);
			philo->meal->finished_meal = 1;
		}
		if (philo->meal->finished_meal)
			break ;
		eating_elapsed_time = get_relative_milliseconds(timestamp);
	}
}

void	philo_sleeping(t_philosopher *philo)
{
	long	timestamp;
	long	sleeping_elapsed_time;
	long	death_elapsed_time;

	timestamp = print_action(SLEEPING, philo);
	sleeping_elapsed_time = get_relative_milliseconds(timestamp);
	while (timestamp <= philo->meal->data->time_to_sleep)
	{
		death_elapsed_time = get_relative_milliseconds(philo->eating_timestamp);
		if (death_elapsed_time > philo->meal->data->time_to_die)
		{
			print_action(DIED, philo);
			philo->meal->finished_meal = 1;
		}
		if (philo->meal->finished_meal)
			break ;
		sleeping_elapsed_time = get_relative_milliseconds(timestamp);
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

