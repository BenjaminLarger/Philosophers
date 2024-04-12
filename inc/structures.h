/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:35:56 by blarger           #+#    #+#             */
/*   Updated: 2024/04/12 13:14:53 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
#include "philosophers.h"

/**
 * @brief A structure to represent a fork.
 *
 * Each fork is represented as a mutex, which can be locked and unlocked.
 * In the context of the dining philosophers problem, a fork is a shared resource
 * that philosophers must acquire before they can eat. Each philosopher shares a fork
 * with the philosopher to their left and the philosopher to their right.
 * Also we associate each philo with a fork.
 */
typedef struct	s_fork
{
	pthread_mutex_t	mutex;
	bool			is_available;
}				t_fork;

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
	t_fork				fork;
	struct s_philo		*next;
	struct s_philo		*prev;
	bool				is_sleeping;
	bool				is_eating;
	bool				is_thinking;
	bool				is_dead;
	int					last_ate;
	int					index;// not used yet
	//add a mutex ?
}					t_philo;

/**
 * @brief A structure to represent the settings for the simulation.
 *
 * This structure includes the number of philosophers, the time a philosopher
 * takes to die without eating, the time a philosopher takes to eat, the time
 * a philosopher spends sleeping, and the maximum number of times a philosopher
 * can eat. It also includes a pointer to the first philosopher in the list.
 */
typedef struct	s_setting
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_time_to_eat;
	bool				max_time_to_eat_set;
	bool				number_of_philo_is_even;
	struct s_philo		*philos;
}					t_setting;

#endif