/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_meal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:49:12 by ozini             #+#    #+#             */
/*   Updated: 2024/06/10 15:43:22 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_mutexes(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->data->philo_nbr)
	{
		pthread_mutex_init(&meal->forks[i].mtx, NULL);
		pthread_mutex_init(&meal->philosophers[i].eating_time_mutex, NULL);
		pthread_mutex_init(&meal->philosophers[i].meals_eaten_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&meal->start_meal_mutex, NULL);
	pthread_mutex_init(&meal->init_time_mutex, NULL);
	pthread_mutex_init(&meal->print_mutex, NULL);
	pthread_mutex_init(&meal->fin_meal_mutex, NULL);
}

static void	init_philo(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->data->philo_nbr)
	{
		pthread_create(&meal->philosophers[i].philo, NULL,
			&philo_routine, &meal->philosophers[i]);
		i++;
	}
}

static void	init_monitor(t_meal *meal)
{
	pthread_create(&meal->monitor, NULL, &monitor_thread, meal);
}

void	begin_meal(t_meal *meal)
{
	init_mutexes(meal);
	init_monitor(meal);
	init_philo(meal);
}
