/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keycatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 17:09:04 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/06 17:09:04 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termcap.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "header.h"

static int	ft_enter_input(char *buf, t_line **array, int y, int i)
{
	if (buf[0] == '\n' && !buf[1])
	{
		ft_restore();
		while (array[y])
		{
			i = 0;
			if (array[y]->vid_rev == 1)
			{
				write(1, array[y]->line, (unsigned long)array[y]->size);
				free(array[y]);
				ft_putstr_fd(" ", 1);
			}
			y++;
		}
		free(array);
		while (ft_is_search(0, 0))
			ft_is_search(0, 1);
		close(ft_open_call());
		exit(0);
	}
	return (0);
}


char		*ft_is_search(char *c, int check)
{
	static char	*word = NULL;
	int			len;

	if (check)
	{
		if ((len = (int)ft_strlen(word)) > 1)
		{
			word[len - 1] = '\0';
			return (word);
		}
		free(word);
		word = NULL;
		return (NULL);
	}
	else if (c && !word)
	{
		word = (char *)malloc(sizeof(char) + 1);
		return ((word = ft_strjoin(word, c)));
	}
	else if (!c && word)
		return (word);
	else if (c && word)
		return ((word = ft_strjoin(word, c)));
	else
		return (NULL);
}

static int	ft_get_search(char *buf)
{
	if (buf[0] >= 33 && buf[0] <= 126)
	{
		ft_is_search(buf, 0);
		ft_check_cursor(1);
		return (1);
	}
	return (0);
}

int			ft_get_input(char *buf, t_cursor *cursor, t_line **array, int *ac)
{
	if (ft_arrow_input(buf, cursor, array, ac) && *ac > 1)
		return (1);
	if (ft_arrow_input_col(buf, cursor, array, ac) && *ac > 1)
		return (1);
	if (ft_space_input(buf, cursor, array, ac))
		return (1);
	if (ft_del_input(buf, cursor, array, ac))
	{
		cursor->check = 1;
		return (1);
	}
	if (ft_enter_input(buf, array, 0, 0))
		return (1);
	if (ft_get_search(buf))
	{
		cursor->check = 1;
		return (1);
	}
	if (ft_esc_input(buf, array))
	{
		cursor->check = 1;
		return (1);
	}
	return (0);
}
