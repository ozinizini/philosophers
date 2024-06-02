/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_handling_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:46:18 by ozini             #+#    #+#             */
/*   Updated: 2024/06/02 16:17:03 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_prompt_data	*init_prompt(int argc, char **argv)
{
	t_prompt_data	*prompt;
	int				i;

	i = 1;
	prompt = malloc(sizeof(t_prompt_data));
	if (prompt == NULL)
	{
		printf("Failed to allocate memory for the data\n");
		return (NULL);
	}
	prompt->nbr_of_meals = -1;
	while (i < argc)
	{
		if (i == 1)
			prompt->philo_nbr = ft_atoi(argv[1]);
		if (i == 2)
			prompt->time_to_die = ft_atoi(argv[2]);
		if (i == 3)
			prompt->time_to_eat = ft_atoi(argv[3]);
		if (i == 4)
			prompt->time_to_sleep = ft_atoi(argv[4]);
		if (i == 5)
			prompt->nbr_of_meals = ft_atoi(argv[5]);
		i++;
	}
	return (prompt);
}

static t_philosopher	*initiliaze_philosophers(int philo_nbr, t_meal *meal)
{
	t_philosopher	*philosophers;
	int				i;

	i = 0;
	philosophers = malloc(philo_nbr * sizeof(t_philosopher));
	if (philosophers == NULL)
	{
		printf("Failed to allocate memory for the philosophers\n");
		return (NULL);
	}
	while (i < philo_nbr)
	{
		philosophers[i].philo_index = i + 1;
		philosophers[i].eating_timestamp = 0;
		philosophers[i].meals_eaten = 0;
		philosophers[i].right_fork = meal->forks[i];
		if (i == philo_nbr -1)
			philosophers[i].left_fork = meal->forks[0];
		else
			philosophers[i].left_fork = meal->forks[i + 1];
		philosophers[i].meal = meal;
		i++;
	}
	return (philosophers);
}

static pthread_mutex_t	*initialize_mutexes(int philo_nbr)
{
	pthread_mutex_t	*mutexes;
	int				i;

	i = 0;
	mutexes = malloc(philo_nbr * sizeof(pthread_mutex_t));
	if (mutexes == NULL)
	{
		printf("Failed to allocate memory for the forks\n");
		return (NULL);
	}
	return (mutexes);
}

t_meal	*initialize_meal(int argc, char **argv)
{
	t_meal	*meal;

	meal = malloc(sizeof(t_meal));
	if (meal == NULL)
	{
		printf("Failed to allocate memory for the meal\n");
		return (NULL);
	}
	meal->initial_time = 0;
	meal->start_meal = 0;
	meal->finished_meal = 0;
	meal->data = init_prompt(argc, argv);
	if (meal->data == NULL)
		return (free(meal), NULL);
	meal->forks = initialize_mutexes(meal->data->philo_nbr);
	if (meal->forks == NULL)
		return (free(meal->data), free (meal), NULL);
	meal->philosophers = initiliaze_philosophers(meal->data->philo_nbr, meal);
	if (meal->philosophers == NULL)
		return (free(meal->data), free(meal->forks), free(meal), NULL);
	return (meal);
}
