/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:24:53 by ozini             #+#    #+#             */
/*   Updated: 2024/06/07 12:45:39 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	print_action(t_philo_action action_type, t_philosopher *philo)
{
	long	timestamp;
	long	absolute_time;

	absolute_time = get_absolute_milliseconds();
	timestamp = absolute_time - read_initial_time(philo->meal);
	pthread_mutex_lock(&philo->meal->print_mutex);
	if (philo->meal->finished_meal)
	{
		pthread_mutex_unlock(&philo->meal->print_mutex);
		return (-1);
	}
	if (action_type == FORK_1)
		printf("%ld %d has taken first fork %d\n", timestamp, philo->philo_index, philo->first_fork->mtx_index);
	else if (action_type == FORK_2)
		printf("%ld %d has taken second fork %d\n", timestamp, philo->philo_index, philo->second_fork->mtx_index);
	else if (action_type == EATING)
	{
		philo->eating_timestamp = absolute_time;
		printf("%ld %d is eating\n", timestamp, philo->philo_index);
	}
	else if (action_type == SLEEPING)
		printf("%ld %d is sleeping\n", timestamp, philo->philo_index);
	else if (action_type == THINKING)
		printf("%ld %d is thinking\n", timestamp, philo->philo_index);
	else if (action_type == DIED)
		printf("%ld %d died\n", timestamp, philo->philo_index);
	pthread_mutex_unlock(&philo->meal->print_mutex);
	return (absolute_time);
}

int	philo_eating(t_philosopher *philo)
{
	long	eating_elapsed_time;

	if (print_action(EATING, philo) == -1)
	{
		pthread_mutex_unlock(&philo->first_fork->mtx);
		pthread_mutex_unlock(&philo->second_fork->mtx);
		return (1);
	}
	if (philo->meal->data->nbr_of_meals != -1)
		philo->meals_eaten++;
	//El eating_elapsed_time es el tiempo transcurrido
	//en milisegundos desde el inicio de la etapa de comer
	eating_elapsed_time = get_relative_milliseconds(philo->eating_timestamp);
	while (eating_elapsed_time <= philo->meal->data->time_to_eat)
	{
		if (philo->meal->finished_meal)
			return (1);
		eating_elapsed_time = get_relative_milliseconds(philo->eating_timestamp);
	}
	pthread_mutex_unlock(&philo->first_fork->mtx);
	pthread_mutex_unlock(&philo->second_fork->mtx);
	return (0);
}

int	philo_sleeping(t_philosopher *philo)
{
	long	absolute_time;
	long	sleeping_elapsed_time;

	absolute_time = print_action(SLEEPING, philo);
	if (absolute_time == -1)
		return (1);
	sleeping_elapsed_time = get_relative_milliseconds(absolute_time);
	while (sleeping_elapsed_time <= philo->meal->data->time_to_sleep)
	{
		if (philo->meal->finished_meal)
			return (1);
		sleeping_elapsed_time = get_relative_milliseconds(absolute_time);
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
	int err;

	err = 0;
	//Coge el tenedor
	if((err = pthread_mutex_lock(&philo->first_fork->mtx)))
		printf("Locking error with errno: %d\n", err);
	if (read_finished_meal(philo->meal))
	{
		pthread_mutex_unlock(&philo->first_fork->mtx);
		return (1);
	}
	if (print_action(FORK_1, philo) == -1)
	{
		pthread_mutex_unlock(&philo->first_fork->mtx);
		return (1);
	}
	if((err = pthread_mutex_lock(&philo->second_fork->mtx)))
		printf("Locking error with errno: %d\n", err);
	if (read_finished_meal(philo->meal))
	{
		pthread_mutex_unlock(&philo->first_fork->mtx);
		pthread_mutex_unlock(&philo->second_fork->mtx);
		return (1);
	}
	if (print_action(FORK_2, philo) == -1)
	{
		pthread_mutex_unlock(&philo->first_fork->mtx);
		pthread_mutex_unlock(&philo->second_fork->mtx);
		return (1);
	}
	return (0);
}
