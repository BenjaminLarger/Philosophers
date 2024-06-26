/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:24:45 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 14:56:32 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_setting	*data;

	if (argc != 5 && argc != 6)
		return (print_error_and_return(ARGS, FAILURE));
	data = malloc(sizeof(t_setting));
	if (!data)
		return (print_error_and_return(MALLOC, -1));
	if (set_state_info_to_struct(argc, argv, data) == FAILURE)
	{
		free(data);
		return (-1);
	}
	data->philos = create_philos_array(data);
	if (init_simulation(data) == FAILURE)
	{
		free(data->philos);
		return (free_print_error(INIT_FAILED, FAILURE, data));
	}
	free(data->philos);
	free(data);
}
