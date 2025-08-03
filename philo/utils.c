/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:59:26 by akella            #+#    #+#             */
/*   Updated: 2025/07/29 23:19:55 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death);
	if (philo->info->dead)
	{
		pthread_mutex_unlock(&philo->info->death);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->info->death);
	return (EXIT_SUCCESS);
}

void	print_philo_status(const char *message, t_philo *philosopher)
{
	long	elapsed_time;

	pthread_mutex_lock(&(philosopher->info->print));
	if (is_dead(philosopher))
	{
		pthread_mutex_unlock(&(philosopher->info->print));
		return ;
	}
	if (message && *message == 'd')
	{
		pthread_mutex_lock(&philosopher->info->death);
		philosopher->info->dead = 1;
		pthread_mutex_unlock(&philosopher->info->death);
	}
	elapsed_time = current_time() - philosopher->info->start_time;
	printf("%ld %d %s\n", elapsed_time, philosopher->id, message);
	pthread_mutex_unlock(&(philosopher->info->print));
}

int	ft_usleep(long milliseconds, t_philo *philo)
{
	unsigned long	start;

	start = current_time();
	while ((current_time() - start) < (unsigned long)milliseconds)
	{
		if (is_dead(philo))
			break ;
		usleep(500);
	}
	return (EXIT_SUCCESS);
}

int	handle_single_philosopher(t_philo *philo)
{
	ft_usleep(philo->info->time_to_die, philo);
	print_philo_status("died", philo);
	return (EXIT_FAILURE);
}
