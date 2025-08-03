/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 03:05:47 by akella            #+#    #+#             */
/*   Updated: 2025/07/31 01:48:43 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	terminate_philo_processes(t_philo *philosopher,
	int *process_ids, int philosopher_count)
{
	int	i;

	i = 0;
	if (philosopher->info->has_meal_limit)
	{
		while (i < philosopher_count)
		{
			waitpid(process_ids[i], NULL, 0);
			i++;
		}
		free(process_ids);
		return (EXIT_SUCCESS);
	}
	sem_wait(philosopher->info->terminate);
	while (i < philosopher_count)
	{
		kill(process_ids[i], SIGTERM);
		i++;
	}
	free(process_ids);
	return (EXIT_SUCCESS);
}

void	print_philosopher_status(char *status_message,
	t_philo *philosopher, int should_unlock)
{
	sem_wait(philosopher->info->wait);
	printf("%zu %d %s\n", (get_current_time() - philosopher->info->start_time),
		philosopher->id, status_message);
	if (!should_unlock)
		sem_post(philosopher->info->wait);
}

void	philosopher_eat(t_philo *philosopher)
{
	sem_wait(philosopher->info->forks);
	print_philosopher_status("has taken a fork", philosopher, 0);
	if (philosopher->info->philos_number == 1)
	{
		safe_usleep(philosopher->info->time_to_die, philosopher);
		print_philosopher_status("died", philosopher, 0);
		philosopher->is_alive = 0;
		sem_post(philosopher->info->terminate);
		sem_wait(philosopher->info->wait);
		return ;
	}
	sem_wait(philosopher->info->forks);
	print_philosopher_status("has taken a fork", philosopher, 0);
	philosopher->last_meal_time = get_current_time();
	print_philosopher_status("is eating", philosopher, 0);
	safe_usleep(philosopher->info->time_to_eat, philosopher);
	philosopher->meals_eaten++;
	sem_post(philosopher->info->forks);
	sem_post(philosopher->info->forks);
}

int	start_philo_routine(t_philo *philosopher)
{
	philosopher->last_meal_time = get_current_time();
	if (philosopher->id % 2 == 0)
		usleep(200);
	while (1)
	{
		philosopher_eat(philosopher);
		if (!philosopher->is_alive)
			sem_post(philosopher->info->terminate);
		philosopher_sleep(philosopher);
		if (!philosopher->is_alive)
			sem_post(philosopher->info->terminate);
		philosopher_think(philosopher);
		if (check_meal_completion(philosopher))
			exit(0);
		if (!philosopher->is_alive)
			sem_post(philosopher->info->terminate);
	}
}
