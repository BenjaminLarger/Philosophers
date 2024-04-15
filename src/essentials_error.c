/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:44:59 by blarger           #+#    #+#             */
/*   Updated: 2024/04/15 15:09:33 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error_and_return(char *str, int to_return)
{
	ft_putstr_fd(str, 2);
	return (to_return);
}

void	print_error_and_exit(char *error_message, int status)
{
	ft_putstr_fd(error_message, 2);
	exit(status);
}

void	free_data_print_error_and_exit(char *error_message, int status, t_setting *data)
{
	if (data->philos)
		free(data->philos);
	free(data);
	ft_putstr_fd(error_message, 2);
	exit(status);
}