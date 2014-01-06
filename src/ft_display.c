
#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "header.h"
#include "../libft/libft.h"

static void		ft_move_cursor_column(int *count, int *y, int *step, int length)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
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

static void		ft_move_cursor(t_line **l, struct winsize *ws, int length, int ac)
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

static void		ft_print_line(t_line **l, struct winsize *ws, int length, int ac)
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
		while ((*l)->line[i] != ' ' && (*l)->line[i] != '\0')
		{
			ft_putchar_fd((*l)->line[i], fd_term);
			i++;
		}
		ft_putstr_fd(ANSI_RESET, fd_term);
		ft_move_cursor(l, ws, length, ac);
		close(fd_term);
	}
	else
	{
		ft_putstr_fd("Error with ft_print_line\n", 2);
		exit (-1);
	}
}

void		ft_print(t_line **l, int ac)
{
	struct winsize	ws;
	int				length;

	ioctl(0, TIOCGWINSZ, &ws);
	length = ft_strlen((*l)->line);
	while(*l)
	{
		ft_print_line(l, &ws, length, ac);
		l++;
	}
}
