/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:12:52 by ozini             #+#    #+#             */
/*   Updated: 2024/06/02 12:40:37 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ultimate_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;

	while (!philo->meal->start_meal)
		;
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

void	destroy_mutexes(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->data->philo_nbr)
	{
		pthread_mutex_destroy(&meal->forks[i]);
		i++;
	}
}


void	init_mutexes(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->data->philo_nbr)
	{
		pthread_mutex_init(&meal->forks[i], NULL);
		i++;
	}
}

void	init_philo(t_meal *meal)
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

void	finish_philo(t_meal *meal)
{
	int	i;

	i = 0;
	while (i < meal->data->philo_nbr)
	{
		pthread_join(meal->philosophers[i].philo, NULL);
		i++;
	}
}

void	begin_meal(t_meal *meal)
{
	init_mutexes(meal);
	init_philo(meal);
	meal->start_meal = 1;
	meal->initial_time = get_absolute_milliseconds();
}

void	end_meal(t_meal *meal)
{
	finish_philo(meal);
	destroy_mutexes(meal);
	//freeing structs missing
}
int main(int argc, char **argv)
{
	t_meal	*meal;

	meal = NULL;
	if (argc == 5 || argc == 6)
	{
		//Comprobar que los datos metidos son todos numéricos.
		//Inicializar los datos (campo 'data' de 'meal')
		meal = initialize_meal(argc, argv);
		if (meal == NULL)
			return (1);
		begin_meal(meal);
		end_meal(meal);
	}
	else
		printf("Incorrect number of arguments\n");
}