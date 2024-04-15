/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:33:20 by blarger           #+#    #+#             */
/*   Updated: 2024/04/15 15:20:55 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/* ERRORS */
# define FAILURE 			1
# define SUCCESS 			0
# define NUMBER_OF_PHILO	"Set at least one philosopher.\n"
# define ARGS				"Program only accept 4 or 5 arguments.\n"
# define INVALID_STATE		"Input parameters are not valid.\n"
# define TIME_TO_SLEEP		"Set a positive time to die.\n"
# define TIME_TO_EAT		"Set a positive time to eat.\n"
# define MAX_TIME_TO_EAT	"Set a positive maximum time eating.\n"
# define MALLOC				"Dynamic allocation malloc failed.\n"
# define INIT_FAILED		"Simulation initialisation failed\n"
# define THREAD_CREATE		"Failed to create thread.\n"
# define THREAD_JOIN		"Failed to join thread.\n"
# define MUTEX_LOCK			"Failed to lock mutex\n"
# define MUTEX_UNLOCK			"Failed to unlock mutex\n"

/* STATE CHANGE */
# define TAKES_FORK				" has taken a fork\n"
# define EATS				" is eating\n"
# define SLEEP				" is sleeping\n"
# define THINKS				" is thinking\n"
# define DIES				" died\n"

#endif