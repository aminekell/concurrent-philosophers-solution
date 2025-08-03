/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:32:39 by akella            #+#    #+#             */
/*   Updated: 2025/07/30 01:39:09 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_status(t_philo *philo)
{
	int		is_eating;

	pthread_mutex_lock(&philo->save_eat);
	is_eating = philo->is_eating;
	pthread_mutex_unlock(&philo->save_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->info->argv_5 && philo->meals >= philo->info->number_of_meals)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (EXIT_FAILURE);
	}
	else if (current_time()
		> (philo->info->time_to_die + philo->last_meal) && is_eating != 1)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		print_philo_status("died", philo);
		return (-1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (EXIT_SUCCESS);
}

static int	check_all_philos(t_philo *philo, int *finished)
{
	int	i;
	int	status;

	*finished = 0;
	i = 0;
	while (i < philo->info->philos_number)
	{
		status = check_philo_status(philo);
		if (status == -1)
			return (-1);
		if (status == 1)
			(*finished)++;
		philo = philo->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

void	*monitor_meal_limit(void *arg)
{
	t_philo	*current_philo;
	int		finished_philosophers;

	current_philo = (t_philo *)arg;
	usleep(1000);
	while (!is_dead(current_philo))
	{
		if (check_all_philos(current_philo, &finished_philosophers) == -1)
			return (NULL);
		if (finished_philosophers == current_philo->info->philos_number)
		{
			pthread_mutex_lock(&current_philo->info->death);
			current_philo->info->all_ate = 1;
			pthread_mutex_unlock(&current_philo->info->death);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
