/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_philo_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:44:08 by akella            #+#    #+#             */
/*   Updated: 2025/07/31 08:59:03 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*create_philosopher_list(t_philo *philosopher_list,
	t_info *simulation_info, int philosopher_count)
{
	t_philo	*new_philosopher;
	int		i;

	i = 0;
	while (i < philosopher_count)
	{
		new_philosopher = create_new_philosopher(i + 1);
		if (!new_philosopher)
			return (cleanup_resources(philosopher_list, i), NULL);
		new_philosopher->info = simulation_info;
		add_philosopher_to_list(&philosopher_list, new_philosopher);
		i++;
	}
	return (philosopher_list);
}
