/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keycatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 17:09:04 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/06 17:09:04 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termcap.h>
#include <curses.h>
#include "../libft/libft.h"
#include "header.h"

static int	ft_arrow_input(char *buf, t_cursor *cursor,
							t_line **array, int *ac)
{
	if (buf[0] == 0x1B && buf[1] == 0x5B && buf[2] == 0x42)
	{
		array[cursor->pos]->underline = 0;
		if (cursor->pos > *ac - 3)
			cursor->pos = 0;
		else
			cursor->pos += 1;
		array[cursor->pos]->underline = 1;
		cursor->check = 1;
		return (1);
	}
	else if (buf[0] == 0x1B && buf[1] == 0x5B && buf[2] == 0x41)
	{
		array[cursor->pos]->underline = 0;
		if (!cursor->pos)
			cursor->pos = *ac - 2;
		else
			cursor->pos -= 1;
		array[cursor->pos]->underline = 1;
		cursor->check = 1;
		return (1);
	}
	return (0);
}

static int	ft_space_input(char *buf, t_cursor *cursor,
							t_line **array, int *ac)
{
	if (buf[0] == ' ')
	{
		if (array[cursor->pos]->vid_rev == 1)
			array[cursor->pos]->vid_rev = 0;
		else
			array[cursor->pos]->vid_rev = 1;
		array[cursor->pos]->underline = 0;
		if (cursor->pos > *ac - 3)
			cursor->pos = 0;
		else
			cursor->pos += 1;
		array[cursor->pos]->underline = 1;
		cursor->check = 1;
		return (1);
	}
	return (0);
}

static int	ft_del_input(char *buf, t_cursor *cursor,
							t_line **array, int *ac)
{
	if (buf[0] == 127 || buf[0] == 8)
	{
		array[cursor->pos]->underline = 0;
		while (array[cursor->pos + 1])
		{
			array[cursor->pos] = array[cursor->pos + 1];
			cursor->pos++;
		}
		array[cursor->pos] = NULL;
		(*ac)--;
		if (*ac == 1)
		{
			buf[0] = 27;
			ft_esc_input(buf, array);
		}
		cursor->pos--;
		if (cursor->pos > *ac - 3)
			cursor->pos = 0;
		else
			cursor->pos += 1;
		array[cursor->pos]->underline = 1;
		cursor->check = 1;
		return (1);
	}
	return (0);
}

static int	ft_enter_input(char *buf, t_line **array, int y, int i)
{
	if (buf[0] == '\n')
	{
		ft_restore();
		tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
		while (array[y])
		{
			i = 0;
			if (array[y]->vid_rev == 1)
			{
				while (array[y]->line[i] != ' ' && array[y]->line[i] != '\0')
				{
					ft_putchar_fd(array[y]->line[i], 1);
					i++;
				}
				free(array[y]);
				ft_putstr_fd(" ", 1);
			}
			y++;
		}
		free(array);
		exit(1);
	}
	return (0);
}

int			ft_get_input(char *buf, t_cursor *cursor, t_line **array, int *ac)
{
	if (ft_arrow_input(buf, cursor, array, ac) && *ac > 1)
		return (1);
	if (ft_space_input(buf, cursor, array, ac))
		return (1);
	if (ft_del_input(buf, cursor, array, ac))
		return (1);
	if (ft_enter_input(buf, array, 0, 0))
		return (1);
	if (ft_esc_input(buf, array))
		return (1);
	return (0);
}
