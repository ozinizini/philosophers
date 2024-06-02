/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_meal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:51:40 by ozini             #+#    #+#             */
/*   Updated: 2024/06/02 12:59:51 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	finish_philo(t_meal *meal)
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
		pthread_mutex_destroy(&meal->forks[i]);
		i++;
	}
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
	finish_philo(meal);
	destroy_mutexes(meal);
	tidy_up_meal(meal);
}
