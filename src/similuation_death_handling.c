/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   similuation_death_handling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:51:09 by blarger           #+#    #+#             */
/*   Updated: 2024/04/16 16:18:31 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	philo_must_die(t_philo *philo)
{
	long long	time_since_last_meal;
	//printf("waiting to die\n");
	//printf("done waiting to die\n");
	lock_mutex(&philo->data->mutex_max_meals);
	time_since_last_meal = current_time_stamp_in_ms() - philo->last_meal;
	unlock_mutex(&philo->data->mutex_max_meals);
	if (time_since_last_meal >= philo->data->time_before_starving)
	{
		printf("time = %lld\n", time_since_last_meal);
		lock_mutex(&philo->data->mutex_death);
		print_state_change(DIES, philo->index, philo, true);
		philo->is_dead = true;
		unlock_mutex(&philo->data->mutex_death);
	}
	return (philo->is_dead);
}

bool	check_if_a_philo_must_exit(t_philo *philo)//change name
{
	bool	must_exit;

	must_exit = false;
	//lock_mutex(&philo->data->mutex_death);
	//printf("waiting for exit %d\n", philo->index);
	lock_mutex(&philo->data->mutex_exit);
	//printf("done waiting for exit %d\n", philo->index);
	if (philo->data->must_exit == true)
		must_exit = true;
	//unlock_mutex(&philo->data->mutex_death);
	unlock_mutex(&philo->data->mutex_exit);
	return (must_exit);
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
			if (philo_must_die(&data->philos[i]) == true
				|| (all_philo_have_finished_max_meals(&data->philos[i])
					== true))
			{
				lock_mutex(&data->mutex_exit);
				to_break = true;
				data->must_exit = true;
				unlock_mutex(&data->mutex_exit);
			}
			i++;
		}
	}
	printf("constant check done\n");
}
