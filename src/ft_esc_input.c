/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 17:08:00 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/06 17:08:00 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termcap.h>
#include <unistd.h>
#include "header.h"

int	ft_check_del(char *buf)
{
	if ((buf[0] == 127 || buf[0] == 8) && !buf[1])
		return (1);
	else if (buf[0] == 0x1b && buf[1] == 0x5B
			&& buf[2] == 0x33 && buf[3] == 0x7E && !buf[4])
		return (1);
	else
		return (0);
}

int	ft_esc_input(char *buf, t_line **array)
{
	int	i;

	if (buf[0] == 27 && !buf[1])
	{
		if (ft_is_search(0, 0))
		{
			ft_is_search(0, 1);
			return (1);
		}
		i = 0;
		ft_restore();
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
		close(ft_open_call());
		exit(0);
	}
	return (0);
}
