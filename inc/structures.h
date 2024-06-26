/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:35:56 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 14:53:01 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "philosophers.h"

/**
 * @brief A structure to represent a philosopher.
 *
 * Each philosopher is represented as a node in a doubly linked list,
 * with pointers to the next and previous philosophers. The philosopher
 * has states to indicate if they are sleeping, eating, or dead, and a
 * timestamp of when they last ate.
 */
typedef struct s_philo
{
	struct s_philo		*next;
	struct s_philo		*prev;
	bool				can_sleep;
	bool				can_eat;
	bool				can_think;
	bool				is_sleeeping;
	bool				is_eating;
	bool				is_thinking;
	bool				is_dead;
	bool				max_meals_reach;
	long long			last_meal;
	int					meals_eaten;
	int					index;// not used yet
	struct s_setting	*data;
	pthread_mutex_t		mutex_max_meal_reach;
	pthread_mutex_t		mutex_fork;
	pthread_mutex_t		mutex_last_meal;
}					t_philo;

/**
 * @brief A structure to represent the settings for the simulation.
 *
 * This structure includes the number of philosophers, the time a philosopher
 * takes to die without eating, the time a philosopher takes to eat, the time
 * a philosopher spends sleeping, and the maximum number of times a philosopher
 * can eat. It also includes a pointer to the first philosopher in the list.
 */
typedef struct s_setting
{
	int					number_of_philo;
	long long			time_before_starving;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_think;
	int					max_meals;
	bool				max_meals_set;
	bool				number_of_philo_is_even;
	long long			program_time_start;
	pthread_mutex_t		mutex_must_exit;
	pthread_mutex_t		mutex_grab_forks;
	pthread_mutex_t		can_write;
	struct s_philo		*philos;
}					t_setting;

#endif