/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:53:35 by akella            #+#    #+#             */
/*   Updated: 2025/07/30 06:49:35 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	validate_time_param(t_info *simulation_info)
{
	if (simulation_info->time_to_die
		< simulation_info->time_to_eat + simulation_info->time_to_sleep)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

t_info	*initialize_semaphores(t_info *simulation_info, int philosopher_count)
{
	sem_unlink("/wait");
	sem_unlink("/terminate");
	sem_unlink("/forks");
	simulation_info->wait = sem_open("/wait", O_CREAT, 0666, 1);
	if (!simulation_info->wait)
		return (NULL);
	simulation_info->terminate = sem_open("/terminate", O_CREAT, 0666, 0);
	if (!simulation_info->terminate)
	{
		sem_unlink("/wait");
		sem_close(simulation_info->wait);
		return (NULL);
	}
	simulation_info->forks = sem_open("/forks", O_CREAT, 0666,
			philosopher_count);
	if (!simulation_info->forks)
	{
		sem_unlink("/wait");
		sem_unlink("/terminate");
		sem_close(simulation_info->terminate);
		sem_close(simulation_info->wait);
		return (NULL);
	}
	return (simulation_info);
}

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000)
		+ (current_time.tv_usec / 1000));
}

t_info	*initialize_simulation_info(int argc, char **argv)
{
	t_info	*simulation_info;

	simulation_info = malloc(sizeof(t_info));
	if (!simulation_info)
		return (NULL);
	simulation_info->philos_number = safe_atoi(argv[1]);
	simulation_info = initialize_semaphores(simulation_info,
			simulation_info->philos_number);
	if (!simulation_info)
		return (free(simulation_info), NULL);
	simulation_info->start_time = get_current_time();
	simulation_info->time_to_die = safe_atoi(argv[2]);
	simulation_info->time_to_eat = safe_atoi(argv[3]);
	simulation_info->time_to_sleep = safe_atoi(argv[4]);
	simulation_info->time_to_think = 0;
	if (simulation_info->time_to_eat > simulation_info->time_to_sleep)
		simulation_info->time_to_think = simulation_info->time_to_eat
			- simulation_info->time_to_sleep;
	simulation_info->has_meal_limit = 0;
	if (argc > 5)
	{
		simulation_info->number_of_meals = safe_atoi(argv[5]);
		simulation_info->has_meal_limit = validate_time_param(simulation_info);
	}
	return (simulation_info);
}
