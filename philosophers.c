/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:12:52 by ozini             #+#    #+#             */
/*   Updated: 2024/06/06 11:35:04 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ultimate_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (!philo->meal->start_meal)
		;
	philo->eating_timestamp = philo->meal->initial_time;
	while (1)
	{
		if (philo_waiting(philo))
			break ;
		if (philo_eating(philo))
			break ;
		if (philo_sleeping(philo))
			break ;
		if (philo_thinking(philo))
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_meal	*meal;

	meal = NULL;
	if (argc == 5 || argc == 6)
	{
		if (argc == 6 && ft_atol(argv[5]) == 0)
			printf("Zero meals entered!\n");
		meal = initialize_meal(argc, argv);
		if (meal == NULL)
			return (1);
		begin_meal(meal);
		end_meal(meal);
	}
	else
		printf("Incorrect number of arguments\n");
	return (0);
}
