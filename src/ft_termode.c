
#include "header.h"

struct termios	g_oldline;

// struct termios *ft_oldline(struct termios *line)
// {

// }

int				ft_putchar_term(int c)
{
	int		fd_term;

	fd_term = open("/dev/tty", O_RDWR);
	if (fd_term)
	{
		write(fd_term, &c, 1);
		close(fd_term);
		return (1);
	}
	else
	{
		ft_restore();
		exit(-1);
	}
	return (1);
}

int				ft_restore(void)
{
	if (tcsetattr(0, TCSANOW, &g_oldline) < 0)
		ft_putstr_fd("Error with ft_restore\n", 2);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_term);
	return (1);
}

int				ft_non_canonical(void)
{
	struct termios	line;

	if (tcgetattr(0, &g_oldline) < 0)
		ft_putstr_fd("Error with ft_canonical_mode (1)\n", 2);
	ft_memcpy(&line, &g_oldline, sizeof(line));
	line.c_lflag &= ~(ICANON|ECHO);
	line.c_cc[VMIN] = 1;
	line.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &line) < 0)
		ft_putstr_fd("Error with ft_canonical_mode (2)\n", 2);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_term);
	return (1);
}
