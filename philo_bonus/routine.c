/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:43:12 by akella            #+#    #+#             */
/*   Updated: 2025/07/30 07:14:05 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_meal_completion(t_philo *philosopher)
{
	if (philosopher->info->has_meal_limit
		&& philosopher->meals_eaten > philosopher->info->number_of_meals)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	philosopher_think(t_philo *philosopher)
{
	print_philosopher_status("is thinking", philosopher, 0);
	safe_usleep(philosopher->info->time_to_think, philosopher);
}

void	philosopher_sleep(t_philo *philosopher)
{
	print_philosopher_status("is sleeping", philosopher, 0);
	safe_usleep(philosopher->info->time_to_sleep, philosopher);
}

int	monitoring(t_philo *philosopher)
{
	size_t	current_time;
	size_t	time_since_meal;

	current_time = get_current_time();
	time_since_meal = current_time - philosopher->last_meal_time;
	if (time_since_meal > philosopher->info->time_to_die)
	{
		print_philosopher_status("died", philosopher, 1);
		philosopher->is_alive = 0;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
