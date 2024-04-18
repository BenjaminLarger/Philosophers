/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_set_state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:49:37 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 17:46:43 by blarger          ###   ########.fr       */
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
