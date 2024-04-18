/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_exchange.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:49:39 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 15:38:17 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_forks_to_philo(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
		return ;
	if (philo->index % 2 == 0)
	{
		philo_grab_forks(philo);
		philo->can_eat = true;
	}
/* 	 else
	{
		data->philos[i].left_handed = true;
	}
	i++;
}
	i--;
	if (data->number_of_philo % 2 != 0)
	{
		printf("left handed set\n");
		data->philos[i].left_handed = true;
	} */
}
/* int	philo_grab_forks(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
		return (FAILURE);
	if (philo->data->max_meals_set == true)
	{
		lock_mutex(&philo->mutex_max_meal_reach);
		if (philo->max_meals_reach == true)
		{
			unlock_mutex(&philo->mutex_max_meal_reach);
			return (FAILURE);
		}
		unlock_mutex(&philo->mutex_max_meal_reach);
	}
	lock_mutex(&philo->data->mutex_grab_forks);
	while (true)
	{
		if (philo->fork_is_available == true
			&& philo->next->fork_is_available == true)
		{
			lock_mutex(&philo->mutex_fork);
			print_state_change(TAKES_FORK, philo->index, philo, true);
			lock_mutex(&philo->next->mutex_fork);
			print_state_change(TAKES_FORK, philo->index, philo, true);
			philo->fork_is_available = false;
			philo->next->fork_is_available = false;
			unlock_mutex(&philo->data->mutex_grab_forks);
			return (SUCCESS);
		}
	}
} */

int	philo_grab_forks(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
		return (FAILURE);
	if (philo->data->max_meals_set == true)
	{
		lock_mutex(&philo->mutex_max_meal_reach);
		if (philo->meals_eaten == philo->data->max_meals)
		{
			unlock_mutex(&philo->mutex_max_meal_reach);
			return (FAILURE);
		}
		unlock_mutex(&philo->mutex_max_meal_reach);
	}
	lock_mutex(&philo->mutex_fork);
	print_state_change(TAKES_FORK, philo->index, philo);
	lock_mutex(&philo->next->mutex_fork);
	print_state_change(TAKES_FORK, philo->index, philo);
	return (SUCCESS);
}

/* int	philo_grab_forks(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
		return (FAILURE);
	if (philo->data->max_meals_set == true)
	{
		lock_mutex(&philo->mutex_max_meal_reach);
		if (philo->max_meals_reach == true)
		{
			unlock_mutex(&philo->mutex_max_meal_reach);
			return (FAILURE);
		}
		unlock_mutex(&philo->mutex_max_meal_reach);
	}
	if (philo->left_handed == true)
	{
		lock_mutex(&philo->next->mutex_fork);
		print_state_change(TAKES_FORK, philo->index, philo, true);
	}
	lock_mutex(&philo->mutex_fork);
	print_state_change(TAKES_FORK, philo->index, philo, true);
	if (philo->left_handed == false)
	{
		lock_mutex(&philo->next->mutex_fork);
		print_state_change(TAKES_FORK, philo->index, philo, true);
	}
	return (SUCCESS);
} */

/* void	philo_drop_forks(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
		return ;
	if (philo->left_handed == true)
		unlock_mutex(&philo->next->mutex_fork);
	unlock_mutex(&philo->mutex_fork);
	if (philo->left_handed == false)
		unlock_mutex(&philo->next->mutex_fork);
} */

void	philo_drop_forks(t_philo *philo)
{
	if (philo->data->number_of_philo == 1)
		return ;
	unlock_mutex(&philo->mutex_fork);
	unlock_mutex(&philo->next->mutex_fork);
}
