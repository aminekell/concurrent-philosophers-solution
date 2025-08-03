/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_numeric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:48:57 by akella            #+#    #+#             */
/*   Updated: 2025/07/24 15:52:52 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_numeric(const char *str)
{
	int	i;

	if (!str)
		return (EXIT_SUCCESS);
	i = skip_spaces(str);
	if (str[i] == '\0')
		return (EXIT_SUCCESS);
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (EXIT_SUCCESS);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
