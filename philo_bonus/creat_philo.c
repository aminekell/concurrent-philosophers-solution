/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:53:35 by akella            #+#    #+#             */
/*   Updated: 2025/07/31 08:58:14 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*get_last_philosopher(t_philo *philosopher)
{
	t_philo	*temp;

	if (!philosopher)
		return (NULL);
	temp = philosopher;
	if (!temp->next)
		return (philosopher);
	while (temp->next != philosopher)
		temp = temp->next;
	return (temp);
}

void	add_philosopher_to_list(t_philo **philosopher_list,
	t_philo *new_philosopher)
{
	t_philo	*last_philosopher;

	if (!philosopher_list || !new_philosopher)
		return ;
	last_philosopher = get_last_philosopher(*philosopher_list);
	if (last_philosopher)
	{
		(*philosopher_list)->prev = new_philosopher;
		new_philosopher->next = (*philosopher_list);
		last_philosopher->next = new_philosopher;
		new_philosopher->prev = last_philosopher;
	}
	else
		*philosopher_list = new_philosopher;
}

void	cleanup_semaphores(t_info *simulation_info)
{
	sem_close(simulation_info->forks);
	sem_close(simulation_info->wait);
	sem_close(simulation_info->terminate);
	sem_unlink("/wait");
	sem_unlink("/terminate");
	sem_unlink("/forks");
}

void	cleanup_resources(t_philo *philosopher, int philosopher_count)
{
	t_philo	*temp_philosopher;
	t_info	*simulation_info;
	int		i;

	i = 0;
	if (!philosopher)
		return ;
	simulation_info = philosopher->info;
	while (i++ < philosopher_count)
	{
		temp_philosopher = philosopher;
		philosopher = philosopher->next;
		free(temp_philosopher);
		temp_philosopher = NULL;
	}
	cleanup_semaphores(simulation_info);
	free(simulation_info);
}

t_philo	*create_new_philosopher(int philosopher_id)
{
	t_philo	*new_philosopher;

	new_philosopher = malloc(sizeof(t_philo));
	if (!new_philosopher)
		return (NULL);
	new_philosopher->id = philosopher_id;
	new_philosopher->is_alive = 1;
	new_philosopher->next = new_philosopher;
	new_philosopher->prev = new_philosopher;
	new_philosopher->meals_eaten = 1;
	return (new_philosopher);
}
