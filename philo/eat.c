/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:30:59 by akella            #+#    #+#             */
/*   Updated: 2025/07/31 11:16:40 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philosopher)
{
	print_philo_status("has taken a fork", philosopher);
	print_philo_status("is eating", philosopher);
	pthread_mutex_lock(&philosopher->save_eat);
	philosopher->is_eating = 1;
	pthread_mutex_unlock(&philosopher->save_eat);
	pthread_mutex_lock(&philosopher->meal_mutex);
	philosopher->last_meal = current_time();
	pthread_mutex_unlock(&philosopher->meal_mutex);
	ft_usleep(philosopher->info->time_to_eat, philosopher);
	pthread_mutex_lock(&philosopher->meal_mutex);
	philosopher->meals++;
	pthread_mutex_unlock(&philosopher->meal_mutex);
	pthread_mutex_unlock(&(philosopher->next->fork));
	pthread_mutex_unlock(&(philosopher->fork));
	pthread_mutex_lock(&philosopher->save_eat);
	philosopher->is_eating = 0;
	pthread_mutex_unlock(&philosopher->save_eat);
}

void	eat(t_philo *philosopher)
{
	pthread_mutex_lock(&(philosopher->fork));
	if (is_dead(philosopher))
	{
		pthread_mutex_unlock(&(philosopher->fork));
		return ;
	}
	print_philo_status("has taken a fork", philosopher);
	if (philosopher->info->philos_number == 1)
	{
		ft_usleep(philosopher->info->time_to_die, philosopher);
		print_philo_status("died", philosopher);
		pthread_mutex_unlock(&(philosopher->fork));
		return ;
	}
	pthread_mutex_lock(&(philosopher->next->fork));
	if (is_dead(philosopher))
	{
		pthread_mutex_unlock(&(philosopher->next->fork));
		pthread_mutex_unlock(&(philosopher->fork));
		return ;
	}
	eating(philosopher);
}
