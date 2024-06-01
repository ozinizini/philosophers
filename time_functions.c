/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:26:57 by ozini             #+#    #+#             */
/*   Updated: 2024/06/01 13:19:15 by ozini            ###   ########.fr       */
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
