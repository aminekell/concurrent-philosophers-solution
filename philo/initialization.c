/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:42:42 by akella            #+#    #+#             */
/*   Updated: 2025/07/31 01:35:29 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*init_mutex(t_info *info)
{
	if (pthread_mutex_init(&info->print, NULL) != 0)
	{
		free(info);
		return (NULL);
	}
	if (pthread_mutex_init(&info->death, NULL) != 0)
	{
		pthread_mutex_destroy(&info->print);
		free(info);
		return (NULL);
	}
	if (pthread_mutex_init(&info->meal_count, NULL) != 0)
	{
		pthread_mutex_destroy(&info->print);
		pthread_mutex_destroy(&info->death);
		free(info);
		return (NULL);
	}
	return (info);
}

int	initialize_philo(t_philo *philo, int size)
{
	int			i;
	pthread_t	monitor;
	t_philo		*head;

	head = philo;
	if (start_philosophers(philo, size))
		return (EXIT_FAILURE);
	if (pthread_create(&monitor, NULL, monitor_meal_limit, head))
	{
		join_threads(head, size);
		return (EXIT_FAILURE);
	}
	pthread_join(monitor, NULL);
	i = 0;
	philo = head;
	while (i < size)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

long	calculate_thinking_time(long eat, long sleep)
{
	if (eat > sleep)
		return (eat - sleep);
	return (0);
}

t_info	*set_info(int ac, char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info = init_mutex(info);
	if (!info)
		return (NULL);
	info->philos_number = safe_atoi(argv[1]);
	info->time_to_die = safe_atoi(argv[2]);
	info->time_to_eat = safe_atoi(argv[3]);
	info->time_to_sleep = safe_atoi(argv[4]);
	info->argv_5 = 0;
	info->dead = 0;
	info->all_ate = 0;
	if (ac > 5)
	{
		info->number_of_meals = safe_atoi(argv[5]);
		info->argv_5 = 1;
	}
	info->time_to_think = calculate_thinking_time(
			info->time_to_eat, info->time_to_sleep);
	info->start_time = current_time();
	return (info);
}

int	start_philosophers(t_philo *philo, int size)
{
	int		i;
	t_philo	*head;

	head = philo;
	i = 0;
	while (i < size)
	{
		if (pthread_create(&(philo->thread), NULL, philosopher_routine, philo))
		{
			join_threads(head, i);
			return (EXIT_FAILURE);
		}
		philo = philo->next;
		i++;
	}
	return (EXIT_SUCCESS);
}
