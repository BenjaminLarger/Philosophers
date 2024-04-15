/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_forks_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:49:39 by blarger           #+#    #+#             */
/*   Updated: 2024/04/15 17:52:48 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_grab_forks(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
		return (FAILURE);
	lock_mutex(philo->fork.mutex_fork);
	print_state_actualization(TAKES_FORK, philo->index, philo, true);
	lock_mutex(philo->next->fork.mutex_fork);
	print_state_actualization(TAKES_FORK, philo->index, philo, true);
	return (SUCCESS);
}

int	philo_drop_forks(t_philo *philo)
{
	unlock_mutex(philo->fork.mutex_fork);
	if (philo->data->number_of_philo > 1)
		unlock_mutex(philo->next->fork.mutex_fork);
	return (SUCCESS);
}
