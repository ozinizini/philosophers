/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_meal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:49:12 by ozini             #+#    #+#             */
/*   Updated: 2024/06/02 13:33:58 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_mutexes(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->data->philo_nbr)
	{
		pthread_mutex_init(&meal->forks[i], NULL);
		i++;
	}
}

static void	init_philo(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->data->philo_nbr)
	{
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
