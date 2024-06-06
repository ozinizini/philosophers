/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_meal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:49:12 by ozini             #+#    #+#             */
/*   Updated: 2024/06/06 12:00:43 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_mutexes(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->data->philo_nbr)
	{
		//No estoy controlando si se produce un error
		//Devuelve 0 cuando todo ha ido bien.
		pthread_mutex_init(&meal->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&meal->start_meal_mut, NULL);
	pthread_mutex_init(&meal->print_mutex, NULL);
	pthread_mutex_init(&meal->fin_meal_mut, NULL);
}

static void	init_philo(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->data->philo_nbr)
	{
		//No estoy controlando el valor de retorno de pthread_create
		pthread_create(&meal->philosophers[i].philo, NULL,
			&ultimate_routine, &meal->philosophers[i]);
		i++;
	}
}

void	begin_meal(t_meal *meal)
{
	init_mutexes(meal);
	init_philo(meal);
	meal->start_meal = 1;
	meal->initial_time = get_absolute_milliseconds();
	//printf("The initial time is %ld\n", meal->initial_time);
}
