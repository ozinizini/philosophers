/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozini <ozini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:41:47 by ozini             #+#    #+#             */
/*   Updated: 2024/06/08 13:57:46 by ozini            ###   ########.fr       */
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
		error_message("Negative numbers are not allowed!\n");
	if (!(*str >= '0' && *str <= '9'))
		error_message("You must enter numbers only!\n");
	return (str);
}

long long	ft_atol(char *str)
{
	long long	number;

	number = 0;
	str = check_valid_number(str);
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	if (number > INT_MAX)
		error_message("The number must not exceed INT MAX\n");
	return (number);
}

void	check_valid_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
		ft_atol(argv[i++]);
	if (argc == 6 && ft_atol(argv[5]) == 0)
		error_message("Zero meals entered, no dinner for you!\n");
	if (ft_atol(argv[1]) == 0)
		error_message("Zero philosophers entered, no dinner for you!\n");
}

/* int main(int argc, char **argv)
{
	int number;

	if(argc == 2)
	{
		number = ft_atol(argv[1]);
		printf("The number entered is %d", number);
	}
} */
