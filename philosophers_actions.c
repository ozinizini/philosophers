/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:24:53 by ozini             #+#    #+#             */
/*   Updated: 2024/06/02 12:28:16 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	print_action(t_philo_action action_type, t_philosopher *philo)
{
	long	timestamp;

	timestamp = get_relative_milliseconds(philo->meal->initial_time);
	pthread_mutex_lock(&philo->meal->print_mutex);
	if (philo->meal->finished_meal)
	{
		pthread_mutex_unlock(&philo->meal->print_mutex);
		return (-1);
	}
	if (action_type == FORK)
		printf("%ld %d has taken a fork\n", timestamp, philo->philo_index);
	else if (action_type == EATING)
	{
		philo->eating_timestamp = timestamp;
		printf("%ld %d is eating\n", timestamp, philo->philo_index);
	}
	else if (action_type == SLEEPING)
		printf("%ld %d is sleeping\n", timestamp, philo->philo_index);
	else if (action_type == THINKING)
		printf("%ld %d is thinking\n", timestamp, philo->philo_index);
	else if (action_type == DIED)
	{
		pthread_mutex_lock(&philo->meal->fin_meal_mut);
		philo->meal->finished_meal = 1;
		pthread_mutex_unlock(&philo->meal->fin_meal_mut);
		printf("%ld %d died\n", timestamp, philo->philo_index);
	}
	pthread_mutex_unlock(&philo->meal->print_mutex);
	return (timestamp);
}

int	philo_eating(t_philosopher *philo)
{
	long	timestamp;
	long	eating_elapsed_time;
	long	death_elapsed_time;

	timestamp = print_action(EATING, philo);
	if (timestamp == -1)
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		return (1);
	}
	philo->meals_eaten++;
	eating_elapsed_time = get_relative_milliseconds(timestamp);
	while (eating_elapsed_time <= philo->meal->data->time_to_eat)
	{
		death_elapsed_time = get_relative_milliseconds(philo->eating_timestamp);
		if (death_elapsed_time > philo->meal->data->time_to_die)
			print_action(DIED, philo);
		if (philo->meal->finished_meal)
			return (1);
		eating_elapsed_time = get_relative_milliseconds(timestamp);
	}
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return (0);
}

int	philo_sleeping(t_philosopher *philo)
{
	long	timestamp;
	long	sleeping_elapsed_time;
	long	death_elapsed_time;

	timestamp = print_action(SLEEPING, philo);
	if (timestamp == -1)
		return (1);
	sleeping_elapsed_time = get_relative_milliseconds(timestamp);
	while (timestamp <= philo->meal->data->time_to_sleep)
	{
		death_elapsed_time = get_relative_milliseconds(philo->eating_timestamp);
		if (death_elapsed_time > philo->meal->data->time_to_die)
			print_action(DIED, philo);
		if (philo->meal->finished_meal)
			return (1);
		sleeping_elapsed_time = get_relative_milliseconds(timestamp);
	}
	return (0);
}

int	philo_thinking(t_philosopher *philo)
{
	if (print_action(THINKING, philo) == -1)
		return (1);
	else
		return (0);
}

int	philo_waiting(t_philosopher *philo)
{
	long	timestamp;
	long	waiting_elapsed_time;
	long	death_elapsed_time;

	pthread_mutex_lock(&philo->right_fork);
	if (philo->meal->finished_meal)
	{
		pthread_mutex_unlock(&philo->right_fork);
		return (1);
	}
	timestamp = print_action(FORK, philo);
	if (timestamp == -1)
	{
		pthread_mutex_unlock(&philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->left_fork);
	waiting_elapsed_time = get_relative_milliseconds(timestamp);
	while (timestamp <= philo->meal->data->time_to_sleep)
	{
		death_elapsed_time = get_relative_milliseconds(philo->eating_timestamp);
		if (death_elapsed_time > philo->meal->data->time_to_die)
			print_action(DIED, philo);
		if (philo->meal->finished_meal)
			return (1);
		waiting_elapsed_time = get_relative_milliseconds(timestamp);
	}
	return (0);
}

