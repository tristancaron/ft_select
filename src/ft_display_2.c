/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 17:27:47 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/12 17:27:48 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include "header.h"
#include "../libft/libft.h"

static void		ft_move_cursor_column(t_col *col)
{
	struct winsize	ws;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("Error in ft_move_cursor_column\n", 2);
	ws.ws_row -= 2;
	if (col->count < ws.ws_row - 1)
	{
		col->count++;
		col->y++;
		ft_putstr_fd(" ", 1);
		tputs(tgoto(tgetstr("cm", NULL), col->step, col->y),
				1, ft_putchar_term);
	}
	else
	{
		col->y = 0;
		col->count = 0;
		col->step += col->max + 1;
		col->max = 0;
		tputs(tgoto(tgetstr("cm", NULL), col->step, col->y),
				1, ft_putchar_term);
	}
}

static void		ft_too_small(t_col *col, int row)
{
	int			fd_term;
	int			i;

	i = 0;
	fd_term = ft_open_call();
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
		col->count = 0;
		col->step = 0;
		col->y = 0;
		col->max = 0;
	}
	else
	{
		ft_putstr_fd("Error in ft_too_small\n", 2);
		exit(0);
	}
}

int				ft_move_cursor(t_line **l, struct winsize *ws, int ac,
								int word)
{
	static t_col	col;

	col.max = ((*l)->size > col.max) ? (*l)->size : col.max;
	if (ac > ws->ws_row && !word)
		ft_move_cursor_column(&col);
	else if (!word)
	{
		col.y++;
		tputs(tgoto(tgetstr("cm", NULL), 0, col.y), 1, ft_putchar_term);
	}
	l++;
	if (!(*l))
	{
		col.y = 0;
		col.count = 0;
		col.step = 0;
		col.max = 0;
	}
	else if (col.step + (*l)->size + 1 > ws->ws_col && ac > ws->ws_row)
	{
		ft_too_small(&col, ws->ws_col);
		return (0);
	}
	return (1);
}

int				ft_check_show(t_line **l, int *ac, struct winsize *ws)
{
	char	*word;

	if ((word = ft_is_search(0, 0)))
	{
		if (!ft_strstr((*l)->line, word))
		{
			(*l)->show = 0;
			(*ac)--;
			ft_move_cursor(l, ws, *ac, 1);
			return (0);
		}
		(*l)->show = 1;
	}
	else
		(*l)->show = 1;
	return (1);
}

void			ft_is_hightlight(t_line **l)
{
	int		i;
	char	*word;

	i = 0;
	word = ft_is_search(0, 0);
	while (i < (*l)->size)
	{
		if (word && (ft_strncmp(word, &(*l)->line[i], ft_strlen(word)) == 0))
		{
			ft_putstr_fd(BOLD, ft_open_call());
			word++;
		}
		else
			ft_putstr_fd(UNBOLD, ft_open_call());
		write(ft_open_call(), &(*l)->line[i], (unsigned long)1);
		i++;
	}
}
