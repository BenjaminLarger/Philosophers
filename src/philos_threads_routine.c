/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_threads_routine.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:31:14 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 15:33:40 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eating_routine(t_philo *philo)
{
	print_state_change(EATS, philo->index, philo);
	lock_mutex(&philo->mutex_last_meal);
	philo->last_meal = current_time_stamp_in_ms();
	unlock_mutex(&philo->mutex_last_meal);
	ft_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	philo_drop_forks(philo);
	if (philo->data->max_meals_set == true)
	{
		if (philo->meals_eaten == philo->data->max_meals)
		{
			lock_mutex(&philo->mutex_max_meal_reach);
			philo->max_meals_reach = true;
			unlock_mutex(&philo->mutex_max_meal_reach);
		}
	}
	philo->can_eat = false;
}

static void	sleeping_routine(t_philo *philo)
{
	print_state_change(SLEEP, philo->index, philo);
	ft_usleep(philo->data->time_to_sleep);
}

static void	*philos_routine(void *philos)
{
	struct s_philo	*philo;

	philo = (struct s_philo *)philos;
	set_forks_to_philo(philo);
	while (true)
	{
		if (philo->can_eat == true)
		{
			eating_routine(philo);
			philo->can_sleep = true;
		}
		if (philo->can_eat == false)
		{
			if (philo->can_sleep == true)
				sleeping_routine(philo);
			if (philo->can_think == true)
				print_state_change(THINKS, philo->index, philo);
			if (philo->data->number_of_philo == 1)
				philo->can_think = false;
			if (philo_grab_forks(philo) == SUCCESS)
				philo->can_eat = true;			
		}
	}
}

int	loop_simulation(t_setting *data)
{
	int				i;
	pthread_t		*threads;

	threads = malloc(sizeof(pthread_t) * data->number_of_philo);
	if (!threads)
		return (free_print_error(MALLOC, FAILURE, data));
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&threads[i], NULL,
				&philos_routine, &data->philos[i]))
		{
			free(threads);
			return (FAILURE);
		}
		i++;
	}
	constant_check_table(data);
	break_simulation(data, threads);
	/* i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (free_print_error(THREAD_JOIN,
					FAILURE, data));
		i++;
	} */
	free(threads);
	return (SUCCESS);
}
