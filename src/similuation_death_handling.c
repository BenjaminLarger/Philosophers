/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   similuation_death_handling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:51:09 by blarger           #+#    #+#             */
/*   Updated: 2024/04/15 17:58:40 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_must_die(t_philo *philo)
{
	//printf("mutex %p wait must die by %d\n", (void*)&philo->data->mutex_death, philo->index);
	lock_mutex(&philo->data->mutex_death);
	//printf("mutex %p locked must die by %d\n", (void*)&philo->data->mutex_death, philo->index);
	if ((current_time_stamp_in_ms() - philo->last_meal) >= philo->data->time_before_starving)
	{
		print_state_actualization(DIES, philo->index, philo, false);
		philo->is_dead = true;
	}
	unlock_mutex(&philo->data->mutex_death);
	//printf("mutex %p unlocked must die by %d\n", (void*)&philo->data->mutex_death, philo->index);
	return (philo->is_dead);
}

bool	check_if_a_philo_must_exit(t_philo *philo)
{
	int		i;
	bool	a_philo_died;

	printf("check if a philo must exit %d\n", philo->index);
	i= 0;
	a_philo_died = false;
	//printf("mutex %p wait check death by %d\n", (void*)&philo->data->mutex_death, philo->index);
	lock_mutex(&philo->data->mutex_death);
	//printf("mutex %p locked check death by %d\n", (void*)&philo->data->mutex_death, philo->index);
	while (i < philo->data->number_of_philo)
	{
		if (philo->data->philos[i].is_dead == true
			|| philo->data->philos[i].max_meals_reach == true)
		{
			a_philo_died = true;
			printf("\tSHOULD EXIT %d\n", philo->index);
		}
		i++;
	}
	printf("befor unlocking mutex %d\n", philo->);
	unlock_mutex(&philo->data->mutex_death);
	printf("after unlocking mutex\n");
	//printf("mutex %p unlocked check death by %d\n", (void*)&philo->data->mutex_death, philo->index);
	return (a_philo_died);
}
