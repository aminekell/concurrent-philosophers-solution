/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:50:37 by akella            #+#    #+#             */
/*   Updated: 2025/07/31 05:26:28 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	int		*process_ids;
	t_philo	*philosopher_list;
	t_info	*simulation_info;
	int		philosopher_count;

	philosopher_list = NULL;
	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	philosopher_count = safe_atoi(argv[1]);
	process_ids = malloc(philosopher_count * sizeof(int));
	if (!process_ids)
		return (EXIT_FAILURE);
	simulation_info = initialize_simulation_info(argc, argv);
	if (!simulation_info)
		return (free(process_ids), EXIT_FAILURE);
	philosopher_list = create_philosopher_list(philosopher_list,
			simulation_info, philosopher_count);
	if (!philosopher_list)
		return (free(process_ids), free(simulation_info), 1);
	initialize_philosopher_processes(philosopher_list,
		process_ids, philosopher_count);
	cleanup_resources(philosopher_list, philosopher_count);
	return (EXIT_SUCCESS);
}
