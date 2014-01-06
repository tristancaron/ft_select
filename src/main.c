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

static void		ft_init_column(char **av)
{
	int		i;
	int		max;
	int		apply;

	i = 1;
	max = 0;
	while (av[i])
	{
		if (max < (int)ft_strlen(av[i]))
			max = (int)ft_strlen(av[i]);
		i++;
	}
	i = 1;
	while (av[i])
	{
		if ((apply = (int)ft_strlen(av[i])) < max)
		{
			while (apply < max)
			{
				av[i] = ft_strjoin(av[i], " ");
				apply++;
			}
		}
		i++;
	}
}

static int		ft_next(int ac, char **av)
{
	t_line		**array;

	if (ac == 1)
	{
		ft_putstr_fd("No args found\n", 2);
		return (-1);
	}
	ft_init_column(av);
	array = ft_get_line(ac, av);
	ft_non_canonical();
	ft_loop_menu(array, ac);
	return (0);
}

int				main(int ac, char **av)
{
	char	*term;
	char	*bp;

	bp = (char *)malloc(sizeof(char) * BUFF_SIZE);
	if (!bp)
	{
		ft_putstr_fd("Error with malloc\n", 2);
		return (-1);
	}
	if ((term = getenv("TERM")) == NULL)
	{
		ft_putstr_fd("Error with getenv\n", 2);
		return (-1);
	}
	if (tgetent(bp, term) != 1)
	{
		ft_putstr_fd("Error with tgetent\n", 2);
		return (-1);
	}
	ft_signal();
	free(bp);
	ft_next(ac, av);
	return (0);
}
