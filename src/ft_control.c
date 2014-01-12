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
#include <termios.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "../libft/libft.h"
#include "header.h"

static void		sigint_win(int sig)
{
	sig = 0;
	close(0);
}

static void		sigint_ctrlc(int sig)
{
	int		i;
	t_line	**array;

	i = 0;
	array = ft_get_array(NULL);
	while (ft_is_search(0, 0))
		ft_is_search(0, 1);
	i = 0;
	ft_restore();
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	sig = 0;
	close(ft_open_call());
	exit(0);
}

static void		sigint_ctrlz(int sig)
{
	if (isatty(1) == 1)
	{
		ft_restore();
		sig = 0;
		signal(SIGWINCH, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		ioctl(0, TIOCSTI, "\032");
	}
}

static void		sigint_cont(int sig)
{
	ft_non_canonical();
	tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
	ft_signal();
	sig = 0;
	close(0);
}

void			ft_signal(void)
{
	signal(SIGWINCH, sigint_win);
	signal(SIGTSTP, sigint_ctrlz);
	signal(SIGINT, sigint_ctrlc);
	signal(SIGCONT, sigint_cont);
	signal(SIGTTIN, sigint_ctrlc);
}
