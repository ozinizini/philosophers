/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:12:52 by ozini             #+#    #+#             */
/*   Updated: 2024/06/01 16:19:23 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int mails = 0;
int lock = 0;
pthread_mutex_t mutex;

void	*ultimate_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
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
		pthread_mutex_init(&mutex, NULL);
		while (i < meal->data->philo_nbr)
		{
			pthread_create(&meal->philosophers[i].philo, NULL,
				&ultimate_routine, &meal->philosophers[i]);
			i++;
		}
		i = 0;
		while (i < meal->data->philo_nbr)
		{
			pthread_join(meal->philosophers[i].philo, NULL);
			i++;
		}
		//free the structs
		pthread_mutex_destroy(&mutex);
	}
	else
		printf("Incorrect number of arguments\n");
}