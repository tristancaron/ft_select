/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 17:10:10 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/06 17:10:10 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>
#include <termios.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "header.h"

int					ft_open_call(void)
{
	static int	fd = 0;
	static int	check = 0;

	if (check == 0)
	{
		check++;
		fd = open("/dev/tty", O_RDWR);
		if (fd)
			return (fd);
		ft_putstr_fd("Error with ft_call_open\n", 2);
		return (0);
	}
	else
		return (fd);
}

struct termios		*ft_oldline(struct termios *line)
{
	static struct termios	*oldline = NULL;

	if (oldline == NULL)
	{
		oldline = (struct termios *)malloc(sizeof(line));
		if (!oldline)
			ft_putstr_fd("Error in ft_oldline\n", 2);
		oldline = line;
		return (line);
	}
	else
		return (oldline);
}

int					ft_putchar_term(int c)
{
	int		fd_term;

	fd_term = ft_open_call();
	if (fd_term)
	{
		write(fd_term, &c, (unsigned long)1);
		return (c);
	}
	else
	{
		ft_restore();
		exit(0);
	}
	return (c);
}

int					ft_restore(void)
{
	struct termios	line;
	struct termios	*oldline;

	oldline = (struct termios *)malloc(sizeof(line));
	if (!oldline)
		ft_putstr_fd("Error in ft_restore\n", 2);
	oldline = ft_oldline(oldline);
	if (tcsetattr(0, TCSANOW, oldline) < 0)
		ft_putstr_fd("Error with ft_restore\n", 2);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_term);
	tputs(tgetstr("te", NULL), 1, ft_putchar_term);
	return (1);
}

int					ft_non_canonical(void)
{
	struct termios	line;
	struct termios	*oldline;

	oldline = (struct termios *)malloc(sizeof(line));
	if (!oldline)
		ft_putstr_fd("Error in ft_non_canonical\n", 2);
	if (tcgetattr(0, oldline) < 0)
		ft_putstr_fd("Error with ft_canonical_mode (1)\n", 2);
	oldline = ft_oldline(oldline);
	ft_memmove(&line, oldline, sizeof(line));
	line.c_lflag &= ~(unsigned long)(ICANON|ECHO);
	line.c_cc[VMIN] = 1;
	line.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &line) < 0)
		ft_putstr_fd("Error with ft_canonical_mode (2)\n", 2);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_term);
	tputs(tgetstr("ti", NULL), 1, ft_putchar_term);
	return (1);
}
