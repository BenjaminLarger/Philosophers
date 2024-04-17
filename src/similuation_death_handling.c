/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   similuation_death_handling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:51:09 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 12:26:29 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_must_die(t_philo *philo)
{
	long long	time_since_last_meal;
	//printf("waiting to die\n");
	//printf("done waiting to die\n");
	lock_mutex(&philo->mutex_last_meal);
	time_since_last_meal = current_time_stamp_in_ms() - philo->last_meal;
	unlock_mutex(&philo->mutex_last_meal);
	if (time_since_last_meal >= philo->data->time_before_starving)
	{
		printf("time since last meal = %lld\n", time_since_last_meal);
		print_state_change(DIES, philo->index, philo, false);
		philo->is_dead = true;
	}
	return (philo->is_dead);
}

