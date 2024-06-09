/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:24:53 by ozini             #+#    #+#             */
/*   Updated: 2024/06/09 16:27:03 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_action(t_philo_action action_type, t_philosopher *philo,
	long timestamp)
{

	pthread_mutex_lock(&philo->meal->print_mutex);
	if (read_finished_meal(philo->meal) && action_type != DIED)
	{
		pthread_mutex_unlock(&philo->meal->print_mutex);
		return (0);
	}
	if (action_type == FORK)
		printf("%ld %d has taken a fork\n", timestamp, philo->philo_index);
	else if (action_type == EATING)
		printf("%ld %d is eating\n", timestamp, philo->philo_index);
	else if (action_type == SLEEPING)
		printf("%ld %d is sleeping\n", timestamp, philo->philo_index);
	else if (action_type == THINKING)
		printf("%ld %d is thinking\n", timestamp, philo->philo_index);
	else if (action_type == DIED)
		printf("%ld %d died\n", timestamp, philo->philo_index);
	pthread_mutex_unlock(&philo->meal->print_mutex);
	return (1);
}

int	philo_eating(t_philosopher *philo)
{
	long	timestamp;
	long	absolute_time;
	long	eating_elapsed_time;

	absolute_time = get_absolute_milliseconds();
	timestamp = absolute_time - read_initial_time(philo->meal);
	philo->eating_timestamp = absolute_time;
	if (!print_action(EATING, philo, timestamp))
		return (release_forks(philo, 1));
	if (philo->meal->data->nbr_of_meals != -1)
		philo->meals_eaten++;
	eating_elapsed_time = get_relative_milliseconds(philo->eating_timestamp);
	while (eating_elapsed_time <= philo->meal->data->time_to_eat)
	{
		if (read_finished_meal(philo->meal))
			return (release_forks(philo, 1));
		eating_elapsed_time = get_relative_milliseconds
			(philo->eating_timestamp);
	}
	return (release_forks(philo, 0));
}

int	philo_sleeping(t_philosopher *philo)
{
	long	timestamp;
	long	absolute_time;
	long	sleeping_elapsed_time;

	absolute_time = get_absolute_milliseconds();
	timestamp = absolute_time - read_initial_time(philo->meal);
	if (!print_action(SLEEPING, philo, timestamp))
		return (1);
	sleeping_elapsed_time = get_relative_milliseconds(absolute_time);
	while (sleeping_elapsed_time <= philo->meal->data->time_to_sleep)
	{
		if (read_finished_meal(philo->meal))
			return (1);
		sleeping_elapsed_time = get_relative_milliseconds(absolute_time);
	}
	return (0);
}

int	philo_thinking(t_philosopher *philo)
{
	long	timestamp;
	long	absolute_time;

	absolute_time = get_absolute_milliseconds();
	timestamp = absolute_time - read_initial_time(philo->meal);
	if (!print_action(THINKING, philo, timestamp))
		return (1);
	else
		return (0);
}

int	philo_waiting(t_philosopher *philo)
{
	int		err;
	long	timestamp;
	long	absolute_time;

	err = 0;
	if ((err = pthread_mutex_lock(&philo->first_fork->mtx)))
		printf("Locking error with errno: %d\n", err);
	absolute_time = get_absolute_milliseconds();
	timestamp = absolute_time - read_initial_time(philo->meal);
	if (read_finished_meal(philo->meal))
		return (release_first_fork(philo));
	if (!print_action(FORK, philo, timestamp))
		return (release_first_fork(philo));
	//Code for one philosopher
	if (philo->first_fork->mtx_index == philo->second_fork->mtx_index)
	{
		while (!read_finished_meal(philo->meal))
			;
		return (release_first_fork(philo));
	}
	if ((err = pthread_mutex_lock(&philo->second_fork->mtx)))
		printf("Locking error with errno: %d\n", err);
	absolute_time = get_absolute_milliseconds();
	timestamp = absolute_time - read_initial_time(philo->meal);
	if (read_finished_meal(philo->meal))
		return (release_forks(philo, 1));
	if (!print_action(FORK, philo, timestamp))
		return (release_forks(philo, 1));
	return (0);
}
