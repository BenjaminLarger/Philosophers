/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_message_in_real_time.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:20:31 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 14:01:04 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	current_time_stamp_in_ms()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
}

/**
 * @brief Prints the state of a given mutex.
 * 
 * This function attempts to lock the provided mutex.
 * If the mutex is already locked,
 * it prints a message indicating that the mutex is locked.
 * If the mutex is not locked,
 * it locks the mutex, prints a message indicating that the mutex
 *  is not locked, and then unlocks the mutex.
 * 
 * @param mutex The mutex to check.
 * @param mutex_id The identifier of the mutex, used for printing.
 */
void	print_state_change(const char *msg, int philo_i,
			t_philo *philo, bool check_table) //return failure to quit ?
{
	long long	time_to_print;

	if (check_table == true)
	{
		lock_mutex(&philo->data->mutex_must_exit);
		if (philo->data->must_exit == true)//use mutex here
		{
			unlock_mutex(&philo->data->mutex_must_exit);
			return ;
		}
		unlock_mutex(&philo->data->mutex_must_exit);
	}
	time_to_print = current_time_stamp_in_ms()
		- philo->data->program_time_start;
	printf("%lldms\t\tphilo %d\t\t%s", time_to_print, philo_i, msg);
}
