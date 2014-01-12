/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 17:22:27 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/06 17:22:28 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termcap.h>
#include <curses.h>
#include "header.h"
#include "../libft/libft.h"

static void		ft_init_column(char **av, int *size)
{
	int		i;
	int		max;

	i = 1;
	max = 0;
	while (av[i])
	{
		if (max < (size[i - 1] = (int)ft_strlen(av[i])))
			max = size[i - 1];
		i++;
	}
}

t_line			**ft_get_array(t_line **array)
{
	static t_line	**sa_array = NULL;

	if (array)
		sa_array = array;
	return (sa_array);
}

static int		ft_next(int ac, char **av)
{
	t_line		**array;
	int			*size;

	if (ac == 1)
	{
		ft_putstr_fd("No args found\n", 2);
		return (-1);
	}
	size = (int *)malloc((unsigned long)ac * sizeof(int));
	ft_init_column(av, size);
	array = ft_get_line(ac, av, size);
	ft_get_array(array);
	ft_non_canonical();
	ft_loop_menu(array, ac);
	return (0);
}

int				main(int ac, char **av)
{
	char	*term;

	if ((term = getenv("TERM")) == NULL)
	{
		ft_putstr_fd("Error with getenv\n", 2);
		return (-1);
	}
	if (tgetent(NULL, term) != 1)
	{
		ft_putstr_fd("Error with tgetent\n", 2);
		return (-1);
	}
	ft_signal();
	ft_next(ac, av);
	return (0);
}
