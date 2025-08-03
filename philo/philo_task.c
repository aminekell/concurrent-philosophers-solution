/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_task.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:39:22 by akella            #+#    #+#             */
/*   Updated: 2025/07/29 23:18:47 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_philo *philo, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->prev;
		i++;
	}
}

void	philo_sleep(t_philo *philo)
{
	print_philo_status("is sleeping", philo);
	ft_usleep(philo->info->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	print_philo_status("is thinking", philo);
	ft_usleep(philo->info->time_to_think, philo);
}

int	check_meals(t_philo *philo)
{
	int	result;

	if (philo->info->argv_5 == 0)
		return (0);
	pthread_mutex_lock(&philo->meal_mutex);
	result = (philo->meals >= philo->info->number_of_meals);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (result);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	return (lst->prev);
}
