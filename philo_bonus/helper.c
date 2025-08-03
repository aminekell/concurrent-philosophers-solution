/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:40:18 by akella            #+#    #+#             */
/*   Updated: 2025/07/28 20:44:04 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_philosopher_status(t_philo *philosopher)
{
	if (!philosopher->is_alive || monitoring(philosopher))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	safe_usleep(size_t milliseconds, t_philo *philosopher)
{
	size_t	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < milliseconds)
	{
		if (check_philosopher_status(philosopher))
			return (EXIT_SUCCESS);
		usleep(500);
	}
	return (EXIT_SUCCESS);
}
