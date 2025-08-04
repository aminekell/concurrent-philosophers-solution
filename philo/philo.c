/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:30:49 by akella            #+#    #+#             */
/*   Updated: 2025/07/31 05:24:53 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_info	*info;
	int		size;

	if (check_args(ac, av))
		return (EXIT_FAILURE);
	size = safe_atoi(av[1]);
	philos = NULL;
	info = set_info(ac, av);
	if (!info)
		return (EXIT_FAILURE);
	philos = create_philosophers(philos, info, size);
	if (!philos)
		return (cleanup_info(info), EXIT_FAILURE);
	if (initialize_philo(philos, size))
		return (destroy_all(philos, size), EXIT_FAILURE);
	return (destroy_all(philos, size), EXIT_SUCCESS);
}
