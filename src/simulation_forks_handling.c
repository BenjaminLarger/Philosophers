/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_forks_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:49:39 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 12:34:13 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_grab_forks(t_philo *philo)
{
	lock_mutex(&philo->mutex_max_meal_reach);
	if (philo->max_meals_reach == true)
	{
		unlock_mutex(&philo->mutex_max_meal_reach);
		return (FAILURE);
	}
	unlock_mutex(&philo->mutex_max_meal_reach);
	if (philo->data->number_of_philo == 1)
		return (FAILURE);
	//printf("waiting for forks\n");
	lock_mutex(&philo->mutex_fork);
	print_state_change(TAKES_FORK, philo->index, philo, true);
	lock_mutex(&philo->next->mutex_fork);
	//printf("done eating for forks\n");
	print_state_change(TAKES_FORK, philo->index, philo, true);
	return (SUCCESS);
}

void	philo_drop_forks(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
		return ;
	//printf("%d wait lock forks\n", philo->index);
	unlock_mutex(&philo->mutex_fork);
	//printf("%d unlock forks\n", philo->index);
	unlock_mutex(&philo->next->mutex_fork);
	//printf("%d unlock forks\n", philo->index);
}
