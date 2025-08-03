/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:33:04 by akella            #+#    #+#             */
/*   Updated: 2025/07/29 23:40:16 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

long	safe_atoi(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = skip_spaces(str);
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	check_value_limits(long value, int index)
{
	if (value <= 0)
	{
		if (index == 5)
			write(2, "Error: meals count must be greater than 0.\n", 43);
		else
			write(2, "Error: Argument must be greater than 0.\n", 41);
		return (EXIT_FAILURE);
	}
	if (value > INT_MAX)
	{
		write(2, "Error: Argument value exceeds INT_MAX.\n", 40);
		return (EXIT_FAILURE);
	}
	if (index == 1 && value > 200)
	{
		write(2,
			"Error: number_of_philosophers must be between 1 and 200.\n",
			58);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_argument_value(char *arg, int index)
{
	long	value;

	if (check_num(arg))
	{
		write(2, "Error: argument must be a positive number.\n", 44);
		return (EXIT_FAILURE);
	}
	value = safe_atoi(arg);
	if (check_value_limits(value, index))
		return (EXIT_FAILURE);
	if ((index == 2 || index == 3 || index == 4) && value < 60)
	{
		if (index == 2)
			write(2, "Error: time_to_die must be at least 60 ms.\n", 44);
		else if (index == 3)
			write(2, "Error: time_to_eat must be at least 60 ms.\n", 44);
		else
			write(2, "Error: time_to_sleep must be at least 60 ms.\n", 46);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error: Wrong number of arguments.\n", 34);
		return (EXIT_FAILURE);
	}
	i = 1;
	while (i < argc)
	{
		if (check_argument_value(argv[i], i))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
