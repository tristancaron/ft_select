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
#include <curses.h>
#include "header.h"

int	ft_esc_input(char *buf, t_line **array)
{
	int	i;

	if (buf[0] == 27)
	{
		i = 0;
		ft_restore();
		tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
		exit(1);
	}
	return (0);
}
