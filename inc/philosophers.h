/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:32:09 by blarger           #+#    #+#             */
/*   Updated: 2024/04/11 18:42:26 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <strings.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include "libft.h"
# include "errors.h"
# include "structures.h"

/* INPUT */
int		set_state_info_to_struct(int argc, char **argv, t_setting *data);
void	create_simulation(t_setting *data);

/* ERROR */
int		print_error_and_return(char *str, int to_return);
void	print_error_and_exit(char *error_message, int status);
void	free_list(t_setting *data);
void	free_list_until_index(t_setting *data, int index);

/* DEV */
void	print_list(t_setting *data);

#endif