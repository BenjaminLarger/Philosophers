/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:23:04 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 12:55:01 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (ft_putstr_fd(MUTEX_LOCK, 2));
}

void	unlock_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
		return (ft_putstr_fd(MUTEX_UNLOCK, 2));
}

bool	update_if_philo_has_reached_max_meals(t_philo *philo)
{
	bool	to_return;

	to_return = false;
	if (philo->data->max_meals_set == true
		&& philo->meals_eaten == philo->data->max_meals)
	{
		lock_mutex(&philo->mutex_max_meal_reach);
		philo->max_meals_reach = true;
		unlock_mutex(&philo->mutex_max_meal_reach);
		to_return = true;
	}
	return (to_return);
}

void	break_simulation(t_setting *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_detach(threads[i]);
		i++;
	}
}

