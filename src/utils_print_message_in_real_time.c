/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_message_in_real_time.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:20:31 by blarger           #+#    #+#             */
/*   Updated: 2024/04/16 16:13:10 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	current_time_stamp_in_ms()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

void	print_state_change(const char *msg, int philo_i,
			t_philo *philo, bool check_table)
{
	long long	time_to_print;

	if (check_table == true
		&& check_if_a_philo_must_exit(philo) == true)//use mutex here
		return ;
	time_to_print = current_time_stamp_in_ms()
		- philo->data->program_time_start;
	printf("%lldms\t\tphilo %d\t\t%s", time_to_print, philo_i, msg);
}
