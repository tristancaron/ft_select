/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 17:28:41 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/12 17:28:41 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
# include <sys/stat.h>
#include "../libft/libft.h"
#include "header.h"

static void		ft_get_ext(t_line **l)
{
	struct stat *f_s;

	f_s = malloc(sizeof(struct stat));
	(*l)->color = (char *)malloc(sizeof(char));
	if (stat((*l)->line, f_s) == -1)
		(*l)->color = NULL;
	if (S_ISDIR(f_s->st_mode))
		(*l)->color = ft_strjoin((*l)->color, BLUE);
	else if (S_ISLNK(f_s->st_mode))
		(*l)->color = ft_strjoin((*l)->color, CYAN);
	else if (S_ISFIFO(f_s->st_mode) || S_ISBLK(f_s->st_mode))
		(*l)->color = ft_strjoin((*l)->color, YELLOW);
	else if (S_ISSOCK(f_s->st_mode))
		(*l)->color = ft_strjoin((*l)->color, PURPLE);
	else if (f_s->st_mode & S_IXUSR)
		(*l)->color = ft_strjoin((*l)->color, RED);
	else
		(*l)->color = NULL;
}

static void		ft_do_back(t_line **l)
{
	struct stat		*f_s;
	int				fd;

	fd = ft_open_call();
	f_s = malloc(sizeof(struct stat));
	if (!ft_strncmp((*l)->color, BLUE, (unsigned long)8))
		ft_putstr_fd(BK_BLUE, fd);
	else if (!ft_strncmp((*l)->color, CYAN, (unsigned long)8))
		ft_putstr_fd(BK_CYAN, fd);
	else if (!ft_strncmp((*l)->color, YELLOW, (unsigned long)8))
		ft_putstr_fd(BK_YELLOW, fd);
	else if (!ft_strncmp((*l)->color, PURPLE, (unsigned long)8))
		ft_putstr_fd(BK_PURPLE, fd);
	else if (!ft_strncmp((*l)->color, RED, (unsigned long)8))
		ft_putstr_fd(BK_RED, fd);
}

int				ft_do_color(t_line **l, int fd_term)
{
	ft_get_ext(l);
	if ((*l)->color)
	{
		if ((*l)->vid_rev)
		{
			ft_do_back(l);
			return (1);
		}
		else
			ft_putstr_fd((*l)->color, fd_term);
		return (1);
	}
	else
		return (0);
}
