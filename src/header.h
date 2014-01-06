#ifndef HEADER_H
# define HEADER_H



# define BUFF_SIZE 5024
# define ANSI_VR "\033[7m"
# define ANSI_UL "\033[4m"
# define ANSI_RESET "\033[0m"

typedef	struct	s_line
{
	char		*line;
	int			vid_rev;
	int			underline;
}				t_line;

typedef	struct	s_cursor
{
	int			pos;
	int			check;
}				t_cursor;

t_line			**ft_get_line(int ac, char **av);
int				ft_non_canonical(void);
int				ft_restore(void);
int				ft_putchar_term(int c);
void			ft_loop_menu(t_line **array, int ac);
void			ft_print(t_line **l, int ac);
int				ft_get_input(char *buf, t_cursor *cursor, t_line **array, int *ac);
void			ft_signal(void);
int				ft_esc_input(char *buf, t_line **array);

#endif
