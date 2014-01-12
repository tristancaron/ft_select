/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keycatch_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 17:28:19 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/12 17:28:19 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "header.h"

static int		ft_rigth(t_cursor *cursor, t_line **array, int *ac)
{
	struct winsize	ws;
	int				nb_col;
	int				s;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		exit(0);
	ws.ws_row -= 2;
	nb_col = ((*ac - 2) / ws.ws_row) + 1;
	array[cursor->pos]->underline = 0;
	s = cursor->pos;
	cursor->pos += ws.ws_row;
	if (cursor->pos > *ac - 2)
		cursor->pos -= (ws.ws_row * nb_col);
	if (cursor->pos < 0)
	{
		if ((cursor->pos + ws.ws_row) < *ac - 2)
			cursor->pos += ws.ws_row;
		else
			cursor->pos = s;
	}
	while (array[cursor->pos]->show == 0)
		ft_rigth(cursor, array, ac);
	array[cursor->pos]->underline = 1;
	cursor->check = 1;
	return (1);
}

static int		ft_left(t_cursor *cursor, t_line **array, int *ac)
{
	struct winsize	ws;
	int				nb_col;
	int				s;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		exit(0);
	ws.ws_row -= 2;
	nb_col = ((*ac - 2) / ws.ws_row) + 1;
	array[cursor->pos]->underline = 0;
	s = cursor->pos;
	cursor->pos -= ws.ws_row;
	if (cursor->pos < 0)
		cursor->pos += (ws.ws_row * nb_col);
	if (cursor->pos > *ac - 2)
	{
		if ((cursor->pos - ws.ws_row) < *ac - 2)
			cursor->pos -= ws.ws_row;
		else
			cursor->pos = s;
	}
	while (array[cursor->pos]->show == 0)
		ft_left(cursor, array, ac);
	array[cursor->pos]->underline = 1;
	cursor->check = 1;
	return (1);
}

int			ft_arrow_input_col(char *buf, t_cursor *cursor,
								t_line **array, int *ac)
{
	if (buf[0] == 0x1B && buf[1] == 0x5B && buf[2] == 0x43 && !buf[3])
	{
		ft_rigth(cursor, array, ac);
		return (1);
	}
	else if (buf[0] == 0x1B && buf[1] == 0x5B && buf[2] == 0x44 && !buf[3])
	{
		ft_left(cursor, array, ac);
		return (1);
	}
	return (0);
}
