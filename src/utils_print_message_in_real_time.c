/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_message_in_real_time.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:20:31 by blarger           #+#    #+#             */
/*   Updated: 2024/04/14 17:21:21 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	current_time_stamp_in_ms()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

void	print_state_actualization(const char *message, int philo_index, t_philo *data)
{
	long long	time_to_print;

	if (data->is_dead == true)
		return ;
	time_to_print = current_time_stamp_in_ms() - data->program_time_start;
	printf("%lldms\t\tphilo %d\t\t%s", time_to_print, philo_index, message);
}
