/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:04:33 by ozini             #+#    #+#             */
/*   Updated: 2024/06/12 13:07:58 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*return_null_message(char *message)
{
	printf(RED "%s" RST, message);
	return (NULL);
}

void	*failed_allocation(void)
{
	return (return_null_message("Failed to allocate memory!\n"));
}

int	return_error_message(char *message)
{
	printf(RED "%s" RST, message);
	return (1);
}
