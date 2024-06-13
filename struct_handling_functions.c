/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_handling_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:46:18 by ozini             #+#    #+#             */
/*   Updated: 2024/06/13 09:41:11 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_prompt_data	*init_prompt(int argc, char **argv)
{
	t_prompt_data	*prompt;

	prompt = malloc(sizeof(t_prompt_data));
	if (prompt == NULL)
		return (failed_allocation());
	prompt->nbr_of_meals = -1;
	prompt->philo_nbr = ft_atol(argv[1]);
	prompt->time_to_die = ft_atol(argv[2]);
	prompt->time_to_eat = ft_atol(argv[3]);
	prompt->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		prompt->nbr_of_meals = ft_atol(argv[5]);
	return (prompt);
}

static t_philosopher	*initiliaze_philosophers(int philo_nbr, t_meal *meal)
{
	t_philosopher	*philosophers;
	int				i;

	i = 0;
	philosophers = malloc(philo_nbr * sizeof(t_philosopher));
	if (philosophers == NULL)
		return (failed_allocation());
	while (i < philo_nbr)
	{
		philosophers[i].philo_index = i + 1;
		philosophers[i].eating_timestamp = 0;
		philosophers[i].meals_eaten = 0;
		philosophers[i].first_fork = &meal->forks[(i + 1) % philo_nbr];
		philosophers[i].second_fork = &meal->forks[i];
		if (philosophers[i].philo_index % 2 == 0)
		{
			philosophers[i].first_fork = &meal->forks[i];
			philosophers[i].second_fork = &meal->forks[(i + 1) % philo_nbr];
		}
		philosophers[i].meal = meal;
		i++;
	}
	return (philosophers);
}

static t_mtx	*initialize_mutexes(int philo_nbr)
{
	t_mtx	*mutexes;
	int		i;

	i = 0;
	mutexes = malloc(philo_nbr * sizeof(t_mtx));
	if (mutexes == NULL)
		return (failed_allocation());
	while (i < philo_nbr)
	{
		mutexes[i].mtx_index = i + 1;
		i++;
	}
	return (mutexes);
}

t_meal	*set_up_meal(int argc, char **argv)
{
	t_meal	*meal;

	meal = malloc(sizeof(t_meal));
	if (meal == NULL)
		return (failed_allocation());
	meal->initial_time = 0;
	meal->start_meal = 0;
	meal->finished_meal = 0;
	meal->philos_ready = 0;
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
