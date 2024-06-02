/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:12:52 by ozini             #+#    #+#             */
/*   Updated: 2024/06/02 11:04:49 by ozini            ###   ########.fr       */
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
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
		philo_eating(philo);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		philo_sleeping(philo);
		philo_thinking(philo);
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
int main(int argc, char **argv)
{
	t_meal			*meal;
	int             i;

	meal = NULL;
	i = 0;
	if (argc == 5 || argc == 6)
	{
		//Comprobar que los datos metidos son todos numéricos.
		//Inicializar los datos (campo 'data' de 'meal')
		meal = initialize_meal(argc, argv);
		if (meal == NULL)
			return (1);
		//Inicializando los mutex/tenedores.
		init_mutexes(meal);
		while (i < meal->data->philo_nbr)
		{
			pthread_create(&meal->philosophers[i].philo, NULL,
				&ultimate_routine, &meal->philosophers[i]);
			i++;
		}
		//La comida no se inicia hasta que los filósofos están todos
		//sentados/creados.
		meal->start_meal = 1;
		meal->initial_time = get_absolute_milliseconds();
		i = 0;
		while (i < meal->data->philo_nbr)
		{
			pthread_join(meal->philosophers[i].philo, NULL);
			i++;
		}
		destroy_mutexes(meal);
		//free the structs
	}
	else
		printf("Incorrect number of arguments\n");
}