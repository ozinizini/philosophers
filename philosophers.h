/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:27:45 by ozini             #+#    #+#             */
/*   Updated: 2024/06/01 16:05:12 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_philo_action
{
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_philo_action;

typedef struct prompt_data_s
{
	int		philo_nbr;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_of_meals;
}	t_prompt_data;

typedef struct s_philosopher	t_philosopher;

typedef struct meal_s
{
	t_prompt_data	*data;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	long			initial_time;
	int				finished_meal;
}	t_meal;

struct	s_philosopher
{
	int				philo_index;
	long			eating_timestamp;
	int				meals_eaten;
	pthread_t		philo;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	t_meal			*meal;
};

long	get_absolute_milliseconds(void);
long	get_relative_milliseconds(long initial_time);
int		ft_atoi(char *str);
t_meal	*initialize_meal(int argc, char **argv);
void	philo_eating(t_philosopher *philo);
void	philo_sleeping(t_philosopher *philo);
void	philo_thinking(t_philosopher *philo);


#endif