/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:27:45 by ozini             #+#    #+#             */
/*   Updated: 2024/06/02 15:44:48 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

#define RST "\033[0m"
#define RED "\033[1;31m"

typedef enum e_philo_action
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_philo_action;

typedef struct prompt_data_s
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_of_meals;
}	t_prompt_data;

typedef struct s_philosopher	t_philosopher;

typedef struct meal_s
{
	t_prompt_data	*data;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	fin_meal_mut;
	long			initial_time;
	int				start_meal;
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

long			get_absolute_milliseconds(void);
long			get_relative_milliseconds(long initial_time);
long long		ft_atol(char *str);
void			check_valid_input(int argc, char **argv);
t_meal			*initialize_meal(int argc, char **argv);
int				philo_eating(t_philosopher *philo);
int				philo_sleeping(t_philosopher *philo);
int				philo_thinking(t_philosopher *philo);
int				philo_waiting(t_philosopher *philo);
void			*ultimate_routine(void *arg);

//Starting and ending the dinner routine.

//It initializes the mutexes (forks), creates the
//philosophers (threads), helps synchronize the start
//of the meal and sets up the time when it begins.
void	begin_meal(t_meal *meal);
//It joins the threads, destroys the mutexes
//and frees the table t_table variable.
void	end_meal(t_meal *meal);


#endif