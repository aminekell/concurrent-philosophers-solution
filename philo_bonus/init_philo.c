/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:42:39 by akella            #+#    #+#             */
/*   Updated: 2025/07/31 01:12:07 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	initialize_philosopher_processes(t_philo *philosopher,
		int *process_ids, int philosopher_count)
{
	int	i;

	i = 0;
	while (i < philosopher_count)
	{
		process_ids[i] = fork();
		if (process_ids[i] < 0)
		{
			while (--i >= 0)
				kill(process_ids[i], SIGTERM);
			free(process_ids);
			write(2, "Error: fork() failed\n", 22);
			return (EXIT_FAILURE);
		}
		if (process_ids[i] == 0)
		{
			start_philo_routine(philosopher);
			break ;
		}
		philosopher = philosopher->next;
		i++;
	}
	return (terminate_philo_processes(philosopher,
			process_ids, philosopher_count));
}
