/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_meal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:49:12 by ozini             #+#    #+#             */
/*   Updated: 2024/06/06 16:27:19 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_mutexes(t_meal *meal)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < meal->data->philo_nbr)
	{
		//No estoy controlando si se produce un error
		//Devuelve 0 cuando todo ha ido bien.
		if ((err = pthread_mutex_init(&meal->forks[i].mtx, NULL)))
			printf("Mutex initialization failed, err: %d\n", err);
		i++;
	}
	if ((err = pthread_mutex_init(&meal->start_meal_mutex, NULL)))
		printf("Mutex initialization failed, err: %d\n", err);
	if ((err = pthread_mutex_init(&meal->init_time_mutex, NULL)))
		printf("Mutex initialization failed, err: %d\n", err);
	if ((err = pthread_mutex_init(&meal->print_mutex, NULL)))
		printf("Mutex initialization failed, err: %d\n", err);
	if ((err = pthread_mutex_init(&meal->fin_meal_mutex, NULL)))
		printf("Mutex initialization failed, err: %d\n", err);
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
	set_start_meal(meal);
	set_initial_time(meal);
	//printf("The initial time is %ld\n", meal->initial_time);
}
