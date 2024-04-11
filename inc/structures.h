/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:35:56 by blarger           #+#    #+#             */
/*   Updated: 2024/04/11 19:11:36 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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
	bool				is_sleeping;
	bool				is_eating;
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
	struct s_philo		*philos;
}					t_setting;

#endif