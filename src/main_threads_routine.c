/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_threads_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:57:37 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 14:50:40 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	all_philo_have_finished_max_meals(t_setting *data)
{
	int		i;
	bool	must_exit;

	if (data->max_meals_set == false)
		return (false);
	i = 0;
	must_exit = true;
	while (i < data->number_of_philo)
	{
		lock_mutex(&data->philos[i].mutex_max_meal_reach);
		if (data->philos[i].max_meals_reach == false)
		{
			must_exit = false;
			unlock_mutex(&data->philos[i].mutex_max_meal_reach);
			break ;
		}
		unlock_mutex(&data->philos[i].mutex_max_meal_reach);
		i++;
	}
	if (must_exit == true)
		lock_mutex(&data->can_write);
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
		lock_mutex(&philo->data->can_write);
		print_death(philo->index, philo);
		philo->is_dead = true;
	}
	return (philo->is_dead);
}

void	constant_check_table(t_setting *data)
{
	int		i;
	bool	to_break;

	to_break = false;
	while (to_break == false)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			if (all_philo_have_finished_max_meals(data) == true)
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
	//unlock_mutex(&data->can_write);
}
