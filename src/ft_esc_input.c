/*
* @Author: tcaron
* @Date:   2014-01-06 15:16:24
* @Last Modified by:   tcaron
* @Last Modified time: 2014-01-06 16:25:20
*/

#include "header.h"
#include <stdlib.h>
#include <termcap.h>
#include <curses.h>

int	ft_esc_input(char *buf, t_line **array)
{
	if (buf[0] == 27)
	{
		ft_restore();
		tputs(tgetstr("cl", NULL), 1, ft_putchar_term);
		while (*array)
		{
			array++;
		}
		exit(1);
	}
	return (0);
}
