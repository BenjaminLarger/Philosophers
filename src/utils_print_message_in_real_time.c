/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_print_message_in_real_time.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:20:31 by blarger           #+#    #+#             */
/*   Updated: 2024/04/13 18:02:37 by blarger          ###   ########.fr       */
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

	time_to_print = data->program_time_start - current_time_stamp_in_ms();
	printf("timestamp_in_ms %lld\t\tphilo %d\t\t%s", time_to_print
		, philo_index, message);
}
