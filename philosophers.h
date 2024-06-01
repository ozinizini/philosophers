/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:27:45 by ozini             #+#    #+#             */
/*   Updated: 2024/06/01 13:05:54 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct prompt_data_s
{
	int		philo_nbr;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_of_meals;
	long	initial_time;
}	t_prompt_data;

typedef struct meal_s
{
	t_prompt_data	*data;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	int				finished_meal;
}	t_meal;

typedef struct philosopher_s
{
	int				philo_index;
	pthread_t		philo;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	t_meal			*meal;
}	t_philosopher;

long	get_absolute_microseconds(void);
long	get_relative_microseconds(long initial_time);
int		ft_atoi(char *str);
t_meal	*initialize_meal(int argc, char **argv);

#endif