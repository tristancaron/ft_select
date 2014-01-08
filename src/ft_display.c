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

static void		ft_too_small(int *count, int *y, int *step, int row)
{
	int			fd_term;
	int			i;

	i = 0;
	fd_term = open("/dev/tty", O_RDWR);
	if (fd_term)
	{
		while (i <= row)
		{
			tputs(tgoto(tgetstr("cm", NULL), 0, i), 1, ft_putchar_term);
			tputs(tgetstr("ce", NULL), 1, ft_putchar_term);
			i++;
		}
		tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar_term);
		ft_putstr_fd("Windows too small\n", fd_term);
		*count = 0;
		*step = 0;
		*y = 0;
		close(fd_term);
	}
	else
	{
		ft_putstr_fd("Error in ft_too_small\n", 2);
		exit(0);
	}
}

static int		ft_move_cursor(t_line **l, struct winsize *ws,
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
	if (step + length + 1 > ws->ws_col && ac > ws->ws_row)
	{
		ft_too_small(&count, &y, &step, ws->ws_col);
		return (0);
	}
	return (1);
}

static int		ft_print_line(t_line **l, struct winsize *ws,
								int length, int ac)
{
	int	fd_term;

	fd_term = open("/dev/tty", O_RDWR);
	if (fd_term)
	{
		if ((*l)->underline)
			ft_putstr_fd(ANSI_UL, fd_term);
		if ((*l)->vid_rev)
			ft_putstr_fd(ANSI_VR, fd_term);
		if ((int)ws->ws_col < (*l)->size)
		{
			write(fd_term, &(*l)->line[0], (unsigned long)ws->ws_col - 3);
			write(fd_term, "...", (unsigned long)3);
		}
		else
			write(fd_term, &(*l)->line[0], (unsigned long)(*l)->size);
		ft_putstr_fd(ANSI_RESET, fd_term);
		close(fd_term);
		if (ft_move_cursor(l, ws, length, ac) == 0)
			return (0);
		return (1);
	}
	ft_putstr_fd("Error with ft_print_line\n", 2);
	exit(0);
	return (1);
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
		if (ft_print_line(l, &ws, length, ac) == 0)
			break ;
		l++;
	}
	if (length < ws.ws_col)
		tputs(tgetstr("ce", NULL), 1, ft_putchar_term);
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar_term);
}
