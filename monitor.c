/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:59:24 by ozini             #+#    #+#             */
/*   Updated: 2024/06/07 11:50:53 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_full(t_philosopher *philo)
{
	long	nbr_of_meals;

	nbr_of_meals = philo->meal->data->nbr_of_meals;
	if (nbr_of_meals != -1 && philo->meals_eaten >= nbr_of_meals)
		return (1);
	else
		return (0);
}

int	check_death(t_philosopher *philo)
{
	long	death_elapsed_time;

	if (!philo->eating_timestamp)
		return (0);
	death_elapsed_time = get_relative_milliseconds(philo->eating_timestamp);
	if (death_elapsed_time > philo->meal->data->time_to_die)
	{
		set_finished_meal(philo->meal);
		print_action(DIED, philo);
		return (1);
	}
	else
		return (0);
}

void	*monitor_thread(void *arg)
{
	int		i;
	int		full_counter;
	t_meal	*meal;

	meal = (t_meal *)arg;
	//Aquí tengo que sincronizarlo con los filósofos
	//pero debería empezar antes que ellos, ¿no?
/* 	while (!read_start_meal(meal))
		; */
	set_initial_time(meal);
	set_start_meal(meal);
	//No debería empezar hasta que todos los filósofos estén listos.
	while (!read_finished_meal(meal))
	{
		full_counter = 0;
		i = 0;
		while (i < meal->data->philo_nbr)
		{
			if (check_death(&meal->philosophers[i]))
				break ;
			if (check_full(&meal->philosophers[i]))
				full_counter++;
			i++;
		}
		if (full_counter == meal->data->philo_nbr)
			set_finished_meal(meal);
	}
	printf("Sale\n");
	return (NULL);
}
