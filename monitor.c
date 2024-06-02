/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:59:24 by ozini             #+#    #+#             */
/*   Updated: 2024/06/02 15:47:46 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_full()
{
	
}

int	check_death(t_philosopher *philo)
{
	long	death_elapsed_time;

	death_elapsed_time = get_relative_milliseconds(philo->eating_timestamp);
	if (death_elapsed_time > philo->meal->data->time_to_die)
	{
		print_action(DIED, philo);
		return (1);
	}
	else
		return (0);

}

void	monitor_thread(t_meal *meal)
{
	int	i;

	while (!meal->finished_meal)
	{
		i = 0;
		while (i < meal->data->philo_nbr)
		{
			if (check_death(&meal->philosophers[i]))
				break ;
			
			i++;
		}
	}
}
