/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:24:45 by blarger           #+#    #+#             */
/*   Updated: 2024/04/12 13:21:08 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_setting	data;

	if (argc != 5 && argc != 6)
		return (print_error_and_return(ARGS, FAILURE));
	if (set_state_info_to_struct(argc, argv, &data) == FAILURE)
		return (-1);
	if (init_simulation(&data) == FAILURE)
		return (free_data_print_error_and_exit(INIT_FAILED, FAILURE, &data), -1);
	print_list(&data);
	free_list(&data);
}
