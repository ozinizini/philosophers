/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_meal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:51:40 by ozini             #+#    #+#             */
/*   Updated: 2024/06/10 14:56:33 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	finish_philos(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->data->philo_nbr)
	{
		pthread_join(meal->philosophers[i].philo, NULL);
		i++;
	}
}

static void	destroy_mutexes(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->data->philo_nbr)
	{
		pthread_mutex_destroy(&meal->forks[i].mtx);
		pthread_mutex_destroy(&meal->philosophers[i].eating_time_mutex);
		pthread_mutex_destroy(&meal->philosophers[i].meals_eaten_mutex);
		i++;
	}
	pthread_mutex_destroy(&meal->start_meal_mutex);
	pthread_mutex_destroy(&meal->init_time_mutex);
	pthread_mutex_destroy(&meal->print_mutex);
	pthread_mutex_destroy(&meal->fin_meal_mutex);
}

static void	finish_monitor(t_meal *meal)
{
	pthread_join(meal->monitor, NULL);
}

static void	tidy_up_meal(t_meal *meal)
{
	free(meal->data);
	free(meal->philosophers);
	free(meal->forks);
	free(meal);
}

void	end_meal(t_meal *meal)
{
	finish_monitor(meal);
	finish_philos(meal);
	destroy_mutexes(meal);
	tidy_up_meal(meal);
}
