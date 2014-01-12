/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keycatch_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 17:28:29 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/12 17:28:29 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "header.h"

int				ft_down_arrow(t_cursor *cursor, t_line **array, int *ac)
{
	array[cursor->pos]->underline = 0;
	if (cursor->pos > *ac - 3)
		cursor->pos = 0;
	else
		cursor->pos += 1;
	while (array[cursor->pos]->show == 0)
	{
		if (cursor->pos > *ac - 3)
			cursor->pos = 0;
		else
			cursor->pos += 1;
	}
	array[cursor->pos]->underline = 1;
	cursor->check = 1;
	return (1);
}

int				ft_arrow_input(char *buf, t_cursor *cursor,
								t_line **array, int *ac)
{
	if (buf[0] == 0x1B && buf[1] == 0x5B && buf[2] == 0x42 && !buf[3])
		return (ft_down_arrow(cursor, array, ac));
	else if (buf[0] == 0x1B && buf[1] == 0x5B && buf[2] == 0x41 && !buf[3])
	{
		array[cursor->pos]->underline = 0;
		if (!cursor->pos)
			cursor->pos = *ac - 2;
		else
			cursor->pos -= 1;
		while (array[cursor->pos]->show == 0)
		{
			if (!cursor->pos)
				cursor->pos = *ac - 2;
			else
				cursor->pos -= 1;
		}
		array[cursor->pos]->underline = 1;
		cursor->check = 1;
		return (1);
	}
	return (0);
}

int				ft_space_input(char *buf, t_cursor *cursor,
							t_line **array, int *ac)
{
	if (buf[0] == ' ' && !buf[1])
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

static void		ft_generate_esc(char *buf, t_line **l)
{
	buf[0] = 27;
	ft_esc_input(buf, l);
}

int				ft_del_input(char *buf, t_cursor *cursor,
								t_line **array, int *ac)
{
	int	s;

	s = cursor->pos;
	if (ft_check_del(buf))
	{
		while (array[cursor->pos + 1])
		{
			array[cursor->pos] = array[cursor->pos + 1];
			cursor->pos++;
		}
		array[cursor->pos] = NULL;
		(*ac)--;
		if (*ac == 1)
			ft_generate_esc(buf, array);
		cursor->pos = (s == 0) ? s : s - 1;
		if (ft_is_search(0, 0) && !ft_no_found(array))
		{
			cursor->pos = (s + 1 < *ac) ? s : s - 1;
			ft_reshow_c(cursor, array, *ac);
		}
		else
			array[cursor->pos]->underline = 1;
		return (1);
	}
	return (0);
}
