/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:41:40 by ozini             #+#    #+#             */
/*   Updated: 2024/06/13 09:50:39 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	read_philos_ready(t_meal *meal)
{
	int	philos_ready;

	pthread_mutex_lock(&meal->philos_ready_mutex);
	philos_ready = meal->philos_ready;
	pthread_mutex_unlock(&meal->philos_ready_mutex);
	return (philos_ready);
}

void	set_philos_ready(t_meal *meal)
{
	pthread_mutex_lock(&meal->philos_ready_mutex);
	meal->philos_ready = 1;
	pthread_mutex_unlock(&meal->philos_ready_mutex);
}