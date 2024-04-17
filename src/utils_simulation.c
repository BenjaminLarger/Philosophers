/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:23:04 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 14:08:14 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philos_ready_to_state(t_setting *data, char *state)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < data->number_of_philo)
	{
		if (!(ft_strcmp(state, EATS)))
			count++;
		else if (!(ft_strcmp(state, SLEEP))
			&& data->philos[i].can_eat == true)
			count++;
		else if (!(ft_strcmp(state, THINKS))
			&& data->philos[i].can_think == true)
			count++;
		else if (!(ft_strcmp(state, TAKES_FORK))
			&& data->philos[i].can_sleep == true)
			count++;
		i++;
	}
	return (count);
}

void	lock_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (print_error_and_exit(MUTEX_LOCK, EXIT_FAILURE));
}

void	unlock_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
		return (print_error_and_exit(MUTEX_UNLOCK, EXIT_FAILURE));
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

bool	all_philo_have_finished_max_meals(t_philo *philo)
{
	int		i;
	bool	must_exit;

	if (philo->data->max_meals_set == false)
		return false;
	i = 0;
	must_exit = true;
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
		lock_mutex(&philo->data->mutex_must_exit);
		printf("\tthey have all eaten\n");
		philo->data->must_exit = true;
		unlock_mutex(&philo->data->mutex_must_exit);
	}
	return (must_exit);
}
bool	check_if_a_philo_must_exit(t_philo *philo)
{
	lock_mutex(&philo->data->mutex_must_exit);
	if (philo->data->must_exit == true)//use mutex here
	{
		unlock_mutex(&philo->data->mutex_must_exit);
		return (true);
	}
	unlock_mutex(&philo->data->mutex_must_exit);
	return (false);
}
