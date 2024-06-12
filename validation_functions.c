/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:41:47 by ozini             #+#    #+#             */
/*   Updated: 2024/06/12 12:55:14 by ozini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*check_valid_number(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (return_null_message("Negative numbers are not allowed!\n"));
	if (!(*str >= '0' && *str <= '9'))
		return (return_null_message("You must enter numbers only!\n"));
	return (str);
}

long long	ft_atol(char *str)
{
	long long	number;

	number = 0;
	str = check_valid_number(str);
	if (str == NULL)
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	if (number > INT_MAX)
	{
		printf(RED "Arguments must not exceed INT MAX!\n" RST);
		return (-1);
	}
	return (number);
}

int	check_invalid_input(int argc, char **argv)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (i < argc)
	{
		if (ft_atol(argv[i++]) == -1)
		{
			error = 1;
			break ;
		}
	}
	if (argc == 6 && ft_atol(argv[5]) == 0)
		error = return_error_message("Zero meals entered!\n");
	if (ft_atol(argv[1]) == 0)
		error = return_error_message("Zero philosophers showed up!\n");
	if (error)
		return (1);
	return (0);
}
