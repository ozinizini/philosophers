/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 12:50:02 by ozini             #+#    #+#             */
/*   Updated: 2024/06/08 12:51:48 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	read_finished_meal(t_meal *meal)
{
	int	finished_meal;

	pthread_mutex_lock(&meal->fin_meal_mutex);
	finished_meal = meal->finished_meal;
	pthread_mutex_unlock(&meal->fin_meal_mutex);
	return (finished_meal);
}

void	set_finished_meal(t_meal *meal)
{
	pthread_mutex_lock(&meal->fin_meal_mutex);
	meal->finished_meal = 1;
	pthread_mutex_unlock(&meal->fin_meal_mutex);
}

int	release_forks(t_philosopher *philo, int return_value)
{
	pthread_mutex_unlock(&philo->first_fork->mtx);
	pthread_mutex_unlock(&philo->second_fork->mtx);
	return (return_value);
}

int	release_first_fork(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->first_fork->mtx);
	return (1);
}
