/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 17:07:12 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/06 17:07:13 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "header.h"
#include "../libft/libft.h"

static void		ft_move_cursor_column(int *count, int *y,
										int *step, int length)
{
	struct winsize	ws;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("Error in ft_move_cursor_column\n", 2);
	if (*count < ws.ws_row - 1)
	{
		(*count)++;
		(*y)++;
		ft_putstr_fd(" ", 1);
		tputs(tgoto(tgetstr("cm", NULL), *step, *y), 1, ft_putchar_term);
	}
	else
	{
		*y = 0;
		*count = 0;
		*step += length + 1;
		tputs(tgoto(tgetstr("cm", NULL), *step, *y), 1, ft_putchar_term);
	}
}

static void		ft_move_cursor(t_line **l, struct winsize *ws,
								int length, int ac)
{
	static int	y = 0;
	static int	count = 0;
	static int	step = 0;

	if (ac > ws->ws_row)
		ft_move_cursor_column(&count, &y, &step, length);
	else
	{
		y++;
		tputs(tgoto(tgetstr("cm", NULL), 0, y), 1, ft_putchar_term);
	}
	l++;
	if (!(*l))
	{
		y = 0;
		count = 0;
		step = 0;
	}
}

static void		ft_print_line(t_line **l, struct winsize *ws,
								int length, int ac)
{
	int	fd_term;
	int	i;

	fd_term = open("/dev/tty", O_RDWR);
	i = 0;
	if (fd_term)
	{
		if ((*l)->underline)
			ft_putstr_fd(ANSI_UL, fd_term);
		if ((*l)->vid_rev)
			ft_putstr_fd(ANSI_VR, fd_term);
		write(fd_term, &(*l)->line[i], (unsigned long)(*l)->size);
		ft_putstr_fd(ANSI_RESET, fd_term);
		ft_move_cursor(l, ws, length, ac);
		close(fd_term);
	}
	else
	{
		ft_putstr_fd("Error with ft_print_line\n", 2);
		exit(0);
	}
}

void			ft_print(t_line **l, int ac)
{
	struct winsize	ws;
	int				length;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("Error in ft_print\n", 2);
	length = (int)ft_strlen((*l)->line);
	while (*l)
	{
		tputs(tgetstr("ce", NULL), 1, ft_putchar_term);
		ft_print_line(l, &ws, length, ac);
		l++;
	}
	tputs(tgetstr("ce", NULL), 1, ft_putchar_term);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar_term);
}
