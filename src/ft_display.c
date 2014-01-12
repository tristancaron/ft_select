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

#include <termcap.h>
#include <sys/ioctl.h>
#include "header.h"
#include "../libft/libft.h"

void			ft_print(t_line **l, int ac, t_cursor *c)
{
	struct winsize	ws;
	static int		reprint = 0;
	int				sa_ac;
	t_line			**sa_l;

	sa_ac = ac;
	sa_l = l;
	reprint = (reprint == 0) ? 1 : 0;
	if (reprint == 1)
		c->check += 1;
	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("Error in ft_print\n", 2);
	ft_clear_screen(&ws.ws_row);
	while (*l)
	{
		if (ft_print_line(l, &ws, &ac) == 0)
			break ;
		l++;
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, ws.ws_row + 1), 1, ft_putchar_term);
	ft_infos_word(ws.ws_col);
}
