/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_message_in_real_time.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:20:31 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 11:41:46 by blarger          ###   ########.fr       */
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
			t_philo *philo) //return failure to quit ?
{
	long long	time_to_print;

	lock_mutex(&philo->data->can_write);
	time_to_print = current_time_stamp_in_ms()
		- philo->data->program_time_start;
	printf("%lldms\t\tphilo %d\t\t%s", time_to_print, philo_i, msg);
	unlock_mutex(&philo->data->can_write);
}

void	print_death(int philo_i, t_philo *philo)
{
	long long	time_to_print;

	time_to_print = current_time_stamp_in_ms()
		- philo->data->program_time_start;
	printf("%lldms\t\tphilo %d\t\t%s", time_to_print, philo_i, DIES);
}

int	ft_usleep(useconds_t usec)
{
	useconds_t	before;
	useconds_t	after;

	before = current_time_stamp_in_ms();
	after = before;
	while (after - before < usec)
	{
		if (usleep(usec) == -1)
			return (-1);
		after = current_time_stamp_in_ms();
	}
	return (0);
}

