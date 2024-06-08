/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:04:33 by ozini             #+#    #+#             */
/*   Updated: 2024/06/08 14:00:16 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*return_null_message(char *message)
{
	printf("Failed to allocate memory for the %s\n", message);
	return (NULL);
}

void	error_message(char *message)
{
	printf(RED "%s" RST, message);
	exit(EXIT_FAILURE);
}
