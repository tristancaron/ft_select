/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 17:09:57 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/06 17:09:58 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include "../libft/libft.h"
#include "header.h"

static int		check_size(void)
{
	struct winsize			ws;
	static unsigned short	width = 0;
	static unsigned short	height = 0;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("Error in check_size\n", 2);
	if (ws.ws_col != width || ws.ws_row != height)
	{
		width = ws.ws_col;
		height = ws.ws_row;
		return (1);
	}
	return (0);
}

int				ft_no_found(t_line **l)
{
	while (*l)
	{
		if ((*l)->show == 1)
			return (0);
		l++;
	}
	return (1);
}

void			ft_do_loop(t_line **array, t_cursor *cursor, int ac, char *path)
{
	char	buf[5];
	int		ret;

	while (1)
	{
		while (cursor->check-- >= 0|| check_size())
			ft_print(array, ac, cursor);
		if (ft_check_cursor(0))
		{
			if (ft_no_found(array))
				continue ;
			ft_reshow_c(cursor, array, ac);
			ft_print(array, ac, cursor);
		}
		if ((ret = (int)read(0, buf, (unsigned long)4)) == -1)
		{
			if (isatty(0) == 0)
				open(path, O_RDWR);
			cursor->check = 1;
			continue ;
		}
		buf[ret] = '\0';
		ft_get_input(buf, cursor, array, &ac);
	}
}

void			ft_loop_menu(t_line **array, int ac)
{
	t_cursor	cursor;
	char		*path;

	cursor.pos = 0;
	cursor.check = 0;
	path = ttyname(0);
	tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
	ft_do_loop(array, &cursor, ac, path);
}
