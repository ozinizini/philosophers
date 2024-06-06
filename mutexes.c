/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:13:01 by ozini             #+#    #+#             */
/*   Updated: 2024/06/06 14:00:39 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	read_start_meal(t_meal *meal)
{
	int	start_meal;

	pthread_mutex_lock(&meal->start_meal_mutex);
	start_meal = meal->start_meal;
	pthread_mutex_unlock(&meal->start_meal_mutex);
	return (start_meal);
}

void	set_start_meal(t_meal *meal)
{
	pthread_mutex_lock(&meal->start_meal_mutex);
	meal->start_meal = 1;
	pthread_mutex_unlock(&meal->start_meal_mutex);
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
