/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   similuation_death_handling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:51:09 by blarger           #+#    #+#             */
/*   Updated: 2024/04/16 10:22:00 by blarger          ###   ########.fr       */
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

static bool	all_philo_have_finished_max_meals(t_philo *philo)
{
	int		i;
	bool	must_exit;

	i = 0;
	must_exit = true;
	while (i < philo->data->number_of_philo)
	{
		if (philo->data->philos[i].max_meals_reach == false)
			must_exit = false;
		i++;
	}
	return (must_exit);
}

bool	check_if_a_philo_must_exit(t_philo *philo)
{
	int		i;
	bool	must_exit;

	printf("check if a philo must exit %d\n", philo->index);
	i= 0;
	must_exit = false;
	//printf("mutex %p wait check death by %d\n", (void*)&philo->data->mutex_death, philo->index);
	lock_mutex(&philo->data->mutex_death);
	//printf("mutex %p locked check death by %d\n", (void*)&philo->data->mutex_death, philo->index);
	while (i < philo->data->number_of_philo)
	{
		if (philo->data->philos[i].is_dead == true)
		{
			must_exit = true;
			printf("\tSHOULD EXIT %d\n", philo->index);
		}
		i++;
	}
	unlock_mutex(&philo->data->mutex_death);
	if (must_exit == false && all_philo_have_finished_max_meals(philo) == true)
		must_exit = true;
	printf("before unlocking mutex %d\n", philo->index);
	printf("after unlocking mutex %d, a philo is dead = %d\n", philo->index, must_exit);
	//printf("mutex %p unlocked check death by %d\n", (void*)&philo->data->mutex_death, philo->index);
	return (must_exit);
}
