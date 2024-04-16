/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:23:04 by blarger           #+#    #+#             */
/*   Updated: 2024/04/16 16:02:55 by blarger          ###   ########.fr       */
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
	lock_mutex(&philo->data->mutex_max_meals);
	if (philo->data->max_meals_set == true
		&& philo->meals_eaten == philo->data->max_meals)
	{
		philo->max_meals_reach = true;
		to_return = true;
	}
	unlock_mutex(&philo->data->mutex_max_meals);
	return (to_return);
}

bool	all_philo_have_finished_max_meals(t_philo *philo)
{
	int		i;
	bool	must_exit;

	if (philo->data->max_meals_set == false)
		return false;
	//printf("waiting max meals\n");
	lock_mutex(&philo->data->mutex_max_meals);
	//printf("done max meals\n");
	i = 0;
	must_exit = true;
	while (i < philo->data->number_of_philo)
	{
		if (philo->data->philos[i].max_meals_reach == false)
			must_exit = false;
		i++;
	}
	unlock_mutex(&philo->data->mutex_max_meals);
	if (must_exit == true)
		printf("\tthey have all eaten\n");
	return (must_exit);
}
