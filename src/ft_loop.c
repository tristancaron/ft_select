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

void			ft_loop_menu(t_line **array, int ac)
{
	t_cursor	cursor;
	char		buf[5];
	int			ret;
	char		*path;

	cursor.pos = 0;
	cursor.check = 0;
	tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
	while (1)
	{
		if (cursor.check || check_size())
			ft_print(array, ac);
		path = ttyname(0);
		if ((ret = (int)read(0, buf, (unsigned long)4)) == -1)
		{
			if (isatty(0) == 0)
				open(path, O_RDWR);
			cursor.check = 1;
			continue ;
		}
		buf[ret] = '\0';
		ft_get_input(buf, &cursor, array, &ac);
	}
}
