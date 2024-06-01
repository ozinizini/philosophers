/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:26:57 by ozini             #+#    #+#             */
/*   Updated: 2024/06/01 10:34:16 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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