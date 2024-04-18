/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_check_table.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:27:23 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 10:00:51 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	all_philo_have_finished_max_meals(t_philo *philo)
{
	int		i;
	bool	must_exit;

	if (philo->data->max_meals_set == false)
		return false;
	i = 0;
	must_exit = true;
	lock_mutex(&philo->data->mutex_must_exit);
	while (i < philo->data->number_of_philo)
	{
		lock_mutex(&philo->mutex_max_meal_reach);
		if (philo->max_meals_reach == false)
			must_exit = false;
		unlock_mutex(&philo->mutex_max_meal_reach);
		i++;
	}
	if (must_exit == true)
	{
		printf("\tthey have all eaten\n");
		philo->data->must_exit = true;
		unlock_mutex(&philo->data->mutex_must_exit);
		lock_mutex(&philo->data->can_write);
	}
	else
		unlock_mutex(&philo->data->mutex_must_exit);
	return (must_exit);
}

bool	philo_must_die(t_philo *philo)
{
	long long	time_since_last_meal;

	lock_mutex(&philo->mutex_last_meal);
	time_since_last_meal = current_time_stamp_in_ms() - philo->last_meal;
	unlock_mutex(&philo->mutex_last_meal);
	if (time_since_last_meal >= philo->data->time_before_starving)
	{
		printf("time = %lld\n", time_since_last_meal);
		lock_mutex(&philo->data->mutex_must_exit);
		philo->data->must_exit = true;
		print_state_change(DIES, philo->index, philo, false);
		philo->is_dead = true;
		unlock_mutex(&philo->data->mutex_must_exit);
		lock_mutex(&philo->data->can_write);
	}
	return (philo->is_dead);
}

void	constant_check_table(t_setting *data, pthread_t *threads)
{
	int		i;
	bool	to_break;

	(void)threads;
	to_break = false;
	while (to_break == false)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			if (all_philo_have_finished_max_meals(&data->philos[i]) == true)
			{
				to_break = true;
				break ;
			}
			if (philo_must_die(&data->philos[i]) == true)
			{
				to_break = true;
				break ;
			}
			i++;
		}
	}
	unlock_mutex(&data->can_write);
	printf("constant check done\n");
}
