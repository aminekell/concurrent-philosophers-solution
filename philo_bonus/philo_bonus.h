/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:56:09 by akella            #+#    #+#             */
/*   Updated: 2025/07/31 08:58:04 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_info
{
	sem_t	*forks;
	sem_t	*wait;
	sem_t	*terminate;
	int		has_meal_limit;
	size_t	start_time;
	size_t	philos_number;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	time_to_think;
	size_t	time_to_die;
	size_t	number_of_meals;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				is_alive;
	size_t			meals_eaten;
	size_t			last_meal_time;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_info			*info;
}	t_philo;

long	safe_atoi(const char *str);
int		skip_spaces(const char *str);
int		check_value_limits(long value, int index);
int		check_argument_value(char *arg, int index);
int		check_args(int argc, char **argv);
int		is_numeric(const char *str);

t_info	*initialize_semaphores(t_info *info, int size);
long	get_current_time(void);
t_info	*initialize_simulation_info(int ac, char **av);

t_philo	*get_last_philosopher(t_philo *philosopher);
void	add_philosopher_to_list(t_philo **philosopher_list,
			t_philo *new_philosopher);
void	cleanup_semaphores(t_info *simulation_info);
void	cleanup_resources(t_philo *philosopher, int philosopher_count);
t_philo	*create_new_philosopher(int philosopher_id);
t_philo	*create_philosopher_list(t_philo *philosopher_list,
			t_info *simulation_info,
			int philosopher_count);

int		terminate_philo_processes(t_philo *philosopher,
			int *process_ids,
			int philosopher_count);
int		check_meal_completion(t_philo *philosopher);
void	philosopher_think(t_philo *philosopher);
void	philosopher_sleep(t_philo *philosopher);
int		monitoring(t_philo *philosopher);
int		check_philosopher_status(t_philo *philosopher);
int		safe_usleep(size_t milliseconds, t_philo *philosopher);
void	print_philosopher_status(char *status_message,
			t_philo *philosopher,
			int should_unlock);
void	philosopher_eat(t_philo *philo);
int		start_philo_routine(t_philo *philo);
int		initialize_philosopher_processes(t_philo *philo,
			int *process_ids,
			int philosopher_count);
int		validate_time_param(t_info *info);

#endif
