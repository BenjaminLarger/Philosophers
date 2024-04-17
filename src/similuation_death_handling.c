/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   similuation_death_handling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:51:09 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 11:50:13 by blarger          ###   ########.fr       */
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
		lock_mutex(&philo->data->mutex_exit);
		philo->data->must_exit = true;
		print_state_change(DIES, philo->index, philo, false);
		unlock_mutex(&philo->data->mutex_exit);
		philo->is_dead = true;
	}
	return (philo->is_dead);
}
/* 
* It might be a good solution to delete this funciton,
* then simply unset thread when simulation is done.
 */
bool	check_if_a_philo_must_exit(t_philo *philo)//change name
{
	bool	must_exit;

	must_exit = false;

	//printf("waiting for exit %d\n", philo->index);
	//printf("%d is wating must_exit\n", philo->index);
	lock_mutex(&philo->data->mutex_exit);
	//printf("%d locked must exit\n", philo->index);
	//printf("done waiting for exit %d\n", philo->index);
	if (philo->data->must_exit == true)
		must_exit = true;
	//unlock_mutex(&philo->data->mutex_death);
	unlock_mutex(&philo->data->mutex_exit);
	//printf("%d unlocked must exit\n", philo->index);
	return (must_exit);
}

