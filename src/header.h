/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 17:10:36 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/06 17:10:37 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <sys/ioctl.h>

# define ANSI_VR "\033[7m"
# define ANSI_UL "\033[4m"
# define ANSI_RESET "\033[0m"
# define BOLD "\033[1m"
# define UNBOLD "\033[22m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define YELLOW "\033[33m"
# define PURPLE "\033[35m"
# define RED "\033[31m"
# define BK_BLUE "\033[44m"
# define BK_CYAN "\033[46m"
# define BK_YELLOW "\033[43m"
# define BK_PURPLE "\033[45m"
# define BK_RED "\033[41m"

typedef struct	s_line
{
	char		*line;
	int			vid_rev;
	int			underline;
	int			size;
	char		*color;
	int			show;
}				t_line;

typedef struct	s_cursor
{
	int			pos;
	int			check;
}				t_cursor;

typedef struct	s_col
{
	int			y;
	int			count;
	int			step;
	int			max;
}				t_col;

t_line			**ft_get_line(int ac, char **av, int *size);
int				ft_non_canonical(void);
int				ft_restore(void);
int				ft_putchar_term(int c);
void			ft_loop_menu(t_line **array, int ac);
void			ft_print(t_line **l, int ac, t_cursor *c);
int				ft_get_input(char *buf, t_cursor *cursor,
								t_line **array, int *ac);
void			ft_signal(void);
int				ft_esc_input(char *buf, t_line **array);
int				ft_check_del(char *buf);
int				ft_open_call(void);
int				ft_do_color(t_line **l, int fd_term);
struct termios	*ft_oldline(struct termios *line);
int				ft_arrow_input_col(char *buf, t_cursor *cursor,
									t_line **array, int *ac);
char			*ft_is_search(char *c, int check);
int				ft_arrow_input(char *buf, t_cursor *cursor,
								t_line **array, int *ac);
void			ft_reshow_c(t_cursor *c, t_line **l, int ac);
int				ft_check_cursor(int check);
t_line			**ft_get_array(t_line **array);
int				ft_space_input(char *buf, t_cursor *cursor,
								t_line **array, int *ac);
int				ft_del_input(char *buf, t_cursor *cursor,
								t_line **array, int *ac);
void			ft_clear_screen(unsigned short *row);
int				ft_print_line(t_line **l, struct winsize *ws, int *ac);
void			ft_infos_word(int col);
int				ft_check_show(t_line **l, int *ac, struct winsize *ws);
void			ft_is_hightlight(t_line **l);
int				ft_move_cursor(t_line **l, struct winsize *ws, int ac,
								int word);
int				ft_no_found(t_line **l);

#endif /* !HEADER_H */
