/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 17:28:00 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/12 17:28:00 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include "header.h"
#include "../libft/libft.h"

int			ft_print_line(t_line **l, struct winsize *ws, int *ac)
{
	if (!ft_check_show(l, ac, ws))
		return (1);
	if ((*l)->underline)
		ft_putstr_fd(ANSI_UL, ft_open_call());
	if ((*l)->vid_rev)
		ft_putstr_fd(ANSI_VR, ft_open_call());
	ft_do_color(l, ft_open_call());
	if ((int)ws->ws_col < (*l)->size)
	{
		write(ft_open_call(), &(*l)->line[0], (unsigned long)ws->ws_col - 3);
		write(ft_open_call(), "...", (unsigned long)3);
	}
	else
		ft_is_hightlight(l);
	ft_putstr_fd(ANSI_RESET, ft_open_call());
	if (ft_move_cursor(l, ws, *ac, 0) == 0)
		return (0);
	return (1);
}

void		ft_clear_screen(unsigned short *row)
{
	unsigned short	i;

	i = 0;
	while (i <= *row)
	{
		tputs(tgoto(tgetstr("cm", NULL), 0, i), 1, ft_putchar_term);
		tputs(tgetstr("ce", NULL), 1, ft_putchar_term);
		i++;
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar_term);
	*row -= 2;
}

int			ft_check_cursor(int check)
{
	static int	do_reshow = 0;

	if (do_reshow == 0 && check)
		do_reshow = check;
	else if (!check)
	{
		if (do_reshow)
		{
			do_reshow = 0;
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

void		ft_reshow_c(t_cursor *c, t_line **l, int ac)
{
	char	buf[4];
	int		check;

	buf[0] = 0x1B;
	buf[1] = 0x5B;
	buf[2] = 0x42;
	buf[3] = '\0';
	check = c->check;
	if (c->pos == 0)
		ft_arrow_input(buf, c, l, &ac);
	if (c->pos != 0)
	{
		buf[2] = 0x41;
		ft_arrow_input(buf, c, l, &ac);
		buf[2] = 0x42;
		ft_arrow_input(buf, c, l, &ac);
	}
	c->check = check;
}

void		ft_infos_word(int col)
{
	char	*word;
	int		len;

	ft_putstr_fd(BK_BLUE, ft_open_call());
	ft_putstr_fd("Word : ", ft_open_call());
	if ((word = ft_is_search(0, 0)))
	{
		ft_putstr_fd(word, ft_open_call());
		ft_putstr_fd("\033[47m \033[0m\033[44m", ft_open_call());
		ft_putstr_fd(" (ESC to cancel)", ft_open_call());
		len = (col - (int)ft_strlen(word)) - 24;
	}
	else
	{
		ft_putstr_fd("\033[47m \033[0m\033[44m", ft_open_call());
		len = (col - (int)ft_strlen(word)) - 8;
	}
	while (len > 0)
	{
		ft_putstr_fd(" ", ft_open_call());
		len--;
	}
	ft_putstr_fd(ANSI_RESET, ft_open_call());
	tputs(tgoto(tgetstr("cm", NULL), 0, 0), 1, ft_putchar_term);
}
