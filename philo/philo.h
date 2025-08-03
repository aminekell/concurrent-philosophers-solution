/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:08:22 by akella            #+#    #+#             */
/*   Updated: 2025/07/31 03:11:34 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

typedef struct s_info
{
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	meal_count;
	int				dead;
	int				all_ate;
	int				argv_5;
	int				philos_number;
	long			start_time;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	long			time_to_die;
	long			number_of_meals;
}	t_info;

typedef struct s_philo
{
	int				id;
	long			meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	save_eat;
	int				is_eating;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_info			*info;
}	t_philo;

void	destroy_all(t_philo *philo, int count);
int		ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lst_new(int data);
long	safe_atoi(const char *str);

int		check_args(int ac, char **av);
long	current_time(void);
t_philo	*ft_lstlast(t_philo *lst);
int		check_args(int argc, char **argv);
int		check_num(const char *str);
int		skip_spaces(const char *str);
int		ft_usleep(long milliseconds, t_philo *philo);

int		handle_single_philosopher(t_philo *philo);
void	eat(t_philo *philosopher);
int		check_meals(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	*monitor_meal_limit(void *arg);
void	join_threads(t_philo *philo, int size);
void	print_philo_status(const char *message, t_philo *philosopher);
void	*philosopher_routine(void *arg);
long	calculate_thinking_time(long eat, long sleep);
int		initialize_philo(t_philo *philo, int size);
void	join_threads(t_philo *philo, int size);
t_info	*set_info(int ac, char **argv);
int		start_philosophers(t_philo *philo, int size);
int		is_dead(t_philo *philo);
t_philo	*create_philosophers(t_philo *philo_list, t_info *info, int total);
int		init_philo_mutexes(t_philo *philo);
void	*philosopher_routine(void *arg);
void	cleanup_info(t_info *info);

#endif