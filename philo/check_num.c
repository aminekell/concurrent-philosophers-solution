/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:48:57 by akella            #+#    #+#             */
/*   Updated: 2025/07/29 23:16:07 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num(const char *str)
{
	int	i;

	if (!str)
		return (EXIT_FAILURE);
	i = skip_spaces(str);
	if (str[i] == '\0')
		return (EXIT_FAILURE);
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (EXIT_FAILURE);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
