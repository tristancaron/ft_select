/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 17:06:40 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/06 17:06:41 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termcap.h>
#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "header.h"

static void		sigint_win(int sig)
{
	sig = 0;
	close(0);
}

static void		sigint_ctrlc(int sig)
{
	ft_restore();
	sig = 0;
	tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_term);
	exit(0);
}

static void		sigint_cont(int sig)
{
	ft_non_canonical();
	tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_term);
	sig = 0;
	close(0);
}

void			ft_signal(void)
{
	signal(SIGWINCH, sigint_win);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGINT, sigint_ctrlc);
	signal(SIGCONT, sigint_cont);
}
