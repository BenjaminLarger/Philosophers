/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_set_state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:49:37 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 12:55:59 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_failure_or_not(t_setting *data)
{
	int	to_return;

	to_return = SUCCESS;
	if (data->number_of_philo % 2 == 0)
		data->number_of_philo_is_even = true;
	else
		data->number_of_philo_is_even = false;
	if (data->number_of_philo < 1)
		to_return = FAILURE;
	if (data->time_before_starving < 0)
		to_return = FAILURE;
	if (data->time_to_sleep < 0)
		to_return = FAILURE;
	if (data->time_to_eat < 0)
		to_return = FAILURE;
	if (data->max_meals == true && data->max_meals < 0)
		to_return = FAILURE;
	return (to_return);
}

void	display_error_message_if_error(t_setting *data)
{
	if (data->number_of_philo < 1)
		ft_putstr_fd(NUMBER_OF_PHILO, 2);
	if (data->time_before_starving < 0)
		ft_putstr_fd(TIME_TO_SLEEP, 2);
	if (data->time_to_sleep < 0)
		ft_putstr_fd(TIME_TO_SLEEP, 2);
	if (data->time_to_eat < 0)
		ft_putstr_fd(TIME_TO_EAT, 2);
	if (data->max_meals_set == true && data->max_meals < 0)
		ft_putstr_fd(MAX_MEALS, 2);
}

int	set_state_info_to_struct(int argc, char **argv, t_setting *data)
{
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_before_starving = (long long)ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->max_meals_set = true;
		data->max_meals = ft_atoi(argv[5]);
	}
	else
		data->max_meals_set = false;
	display_error_message_if_error(data);
	return (is_failure_or_not(data));
}

static t_philo	create_philosopher(t_setting *data, int index)
{
	t_philo	philo;

	philo.meals_eaten = 0;
	philo.index = index;
	philo.next = NULL;
	philo.prev = NULL;
	philo.is_dead = false;
	philo.can_eat = false;
	philo.can_sleep = false;
	philo.can_think = true;
	philo.max_meals_reach = false;
	philo.last_meal = current_time_stamp_in_ms();
	philo.data = data;
	return (philo);
}

t_philo	*create_philos_array(t_setting *data)
{
	int				i;

	data->philos = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philos)
		free_print_error(MALLOC, 0, data);
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philos[i] = create_philosopher(data, i);
		if (data->number_of_philo == 1)
			return (data->philos);
		if (i > 0)
			data->philos[i].prev = &data->philos[i - 1];
		if (i < data->number_of_philo - 1)
			data->philos[i].next = &data->philos[i + 1];
		i++;
	}
	data->philos[0].prev = &data->philos[data->number_of_philo - 1];
	data->philos[i - 1].next = &data->philos[0];
	return (data->philos);
}
