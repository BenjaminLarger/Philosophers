/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_forks_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:49:39 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 14:05:01 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_grab_forks(t_philo *philo)
{
	if (philo->data->max_meals_set == true)
	{
		lock_mutex(&philo->mutex_max_meal_reach);
		if (philo->max_meals_reach == true)
		{
			unlock_mutex(&philo->mutex_max_meal_reach);
			return (FAILURE);
		}
		unlock_mutex(&philo->mutex_max_meal_reach);
	}
	if (philo->data->number_of_philo == 1)
		return (FAILURE);
	lock_mutex(&philo->mutex_fork);
	print_state_change(TAKES_FORK, philo->index, philo, true);
	lock_mutex(&philo->next->mutex_fork);
	print_state_change(TAKES_FORK, philo->index, philo, true);
	return (SUCCESS);
}

void	philo_drop_forks(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
		return ;
	unlock_mutex(&philo->mutex_fork);
	unlock_mutex(&philo->next->mutex_fork);
}
