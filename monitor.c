/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:59:24 by ozini             #+#    #+#             */
/*   Updated: 2024/06/13 13:39:55 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_full(t_philosopher *philo)
{
	long	nbr_of_meals;
	long	meals_eaten;

	nbr_of_meals = philo->meal->data->nbr_of_meals;
	meals_eaten = read_meals_eaten(philo);
	if (nbr_of_meals != -1 && meals_eaten >= nbr_of_meals)
		return (1);
	else
		return (0);
}

int	check_death(t_philosopher *philo)
{
	long	death_elapsed_time;
	long	timestamp;
	long	absolute_time;

	if (!read_eating_time(philo))
		return (0);
	death_elapsed_time = get_relative_milliseconds(read_eating_time(philo));
	if (death_elapsed_time > philo->meal->data->time_to_die)
	{
		set_finished_meal(philo->meal);
		absolute_time = get_absolute_milliseconds();
		timestamp = absolute_time - read_initial_time(philo->meal);
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
	set_initial_time(meal);
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
	return (NULL);
}
