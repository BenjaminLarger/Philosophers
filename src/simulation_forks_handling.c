/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_forks_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:49:39 by blarger           #+#    #+#             */
/*   Updated: 2024/04/14 17:59:37 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_grab_forks(t_philo *philo)
{
	 if (pthread_mutex_lock(philo->fork.mutex_fork) != 0)
		return (FAILURE);//Handle failure
	if (philo_must_die(philo) == true)
		philo->is_dead = true;
	print_state_actualization(TAKES_FORK, philo->index, philo);
	if (pthread_mutex_lock(philo->next->fork.mutex_fork) != 0)
		return (FAILURE);//Handle failure
	print_state_actualization(TAKES_FORK, philo->index, philo);
	return (SUCCESS);
}

int	philo_drop_forks(t_philo *philo)
{
	 if (pthread_mutex_unlock(philo->fork.mutex_fork) != 0)
		return (FAILURE);//Handle failure
	if (pthread_mutex_unlock(philo->next->fork.mutex_fork) != 0)
		return (FAILURE);//Handle failure

	return (SUCCESS);
}