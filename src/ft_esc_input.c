/*
* @Author: tcaron
* @Date:   2014-01-06 15:16:24
* @Last Modified by:   tcaron
* @Last Modified time: 2014-01-06 15:17:08
*/

#include "header.h"

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
