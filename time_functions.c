/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:26:57 by ozini             #+#    #+#             */
/*   Updated: 2024/06/09 16:07:04 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_absolute_milliseconds(void)
{
	struct timeval	tv;
	long			milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (milliseconds);
}

long	get_relative_milliseconds(long initial_time)
{
	long	current_milliseconds;

	current_milliseconds = get_absolute_milliseconds();
	return (current_milliseconds - initial_time);
}

long	get_absolute_microseconds(void)
{
	struct timeval	tv;
	long			microseconds;

	gettimeofday(&tv, NULL);
	microseconds = tv.tv_sec * 1000000 + tv.tv_usec;
	return (microseconds);
}

long	get_relative_microseconds(long initial_time)
{
	long	current_microseconds;

	current_microseconds = get_absolute_microseconds();
	return (current_microseconds - initial_time);
}

void	precise_usleep(t_meal *meal, long timesleep)
{
	long	begin_sleeping;
	long	current_sleep;
	long	elapsed;
	long	rem;

	begin_sleeping = get_absolute_microseconds();
	current_sleep = begin_sleeping;
	while (current_sleep - begin_sleeping < timesleep)
	{
		if (read_finished_meal(meal))
			break ;
		elapsed = get_absolute_microseconds() - begin_sleeping;
		rem = timesleep - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
		{
			while (current_sleep - begin_sleeping < timesleep)
				;
		}
	}
}
