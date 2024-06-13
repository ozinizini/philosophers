/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:24:53 by ozini             #+#    #+#             */
/*   Updated: 2024/06/13 13:33:12 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_action(t_philo_action action_type, t_philosopher *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->meal->print_mutex);
	timestamp = get_relative_milliseconds(read_initial_time(philo->meal));
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
	long	absolute_time;

	absolute_time = get_absolute_milliseconds();
	set_eating_time(philo, absolute_time);
	if (!print_action(EATING, philo))
		return (release_forks(philo, 1));
	if (philo->meal->data->nbr_of_meals != -1)
		increase_meals_eaten(philo);
	if (precise_usleep(philo->meal, philo->meal->data->time_to_eat * 1000))
		return (release_forks(philo, 1));
	return (release_forks(philo, 0));
}

int	philo_sleeping(t_philosopher *philo)
{
	if (!print_action(SLEEPING, philo))
		return (1);
	if (precise_usleep(philo->meal, philo->meal->data->time_to_sleep * 1000))
		return (1);
	return (0);
}

int	philo_thinking(t_philosopher *philo)
{
	long	time_to_think;

	if (!print_action(THINKING, philo))
		return (1);
	else
	{
		if (philo->meal->data->philo_nbr % 2 == 0)
			return (0);
		time_to_think = philo->meal->data->time_to_eat * 2
			- philo->meal->data->time_to_sleep;
		if (time_to_think < 0)
			time_to_think = 0;
		return (precise_usleep(philo->meal, time_to_think * 1000 * 0.42));
	}
}

int	philo_waiting(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->first_fork->mtx);
	if (read_finished_meal(philo->meal)
		|| (!print_action(FORK, philo)))
		return (release_first_fork(philo));
	if (philo->first_fork->mtx_index == philo->second_fork->mtx_index)
	{
		while (!read_finished_meal(philo->meal))
			;
		return (release_first_fork(philo));
	}
	pthread_mutex_lock(&philo->second_fork->mtx);
	if (read_finished_meal(philo->meal)
		|| (!print_action(FORK, philo)))
		return (release_forks(philo, 1));
	return (0);
}
