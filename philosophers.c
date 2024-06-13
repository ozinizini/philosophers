/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:12:52 by ozini             #+#    #+#             */
/*   Updated: 2024/06/13 13:41:05 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (!read_philos_ready(philo->meal))
		;
	while (!read_initial_time(philo->meal))
		;
	if (philo->philo_index % 2 == 0)
		precise_usleep(philo->meal, 30000);
	set_eating_time(philo, read_initial_time(philo->meal));
	while (!read_finished_meal(philo->meal))
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
		if (check_invalid_input(argc, argv))
			return (1);
		meal = set_up_meal(argc, argv);
		if (meal == NULL)
			return (1);
		begin_meal(meal);
		end_meal(meal);
	}
	else
		return (return_error_message("Only 4 arguments are required."
				" An additional argument is optional "
				"when specifying the number of meals\n"));
	return (0);
}
