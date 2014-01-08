/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/06 17:08:21 by tcaron            #+#    #+#             */
/*   Updated: 2014/01/06 17:08:21 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "../libft/libft.h"
#include <stdlib.h>

static t_line	*ft_init_line(char *line, int vid_rev, int underline)
{
	t_line	*result;

	result = (t_line *)malloc(sizeof(t_line));
	if (!result)
	{
		ft_putstr_fd("Error inr ft_init_line\n", 2);
		return (NULL);
	}
	result->line = line;
	result->vid_rev = vid_rev;
	result->underline = underline;
	return (result);
}

t_line			**ft_get_line(int ac, char **av)
{
	t_line		**result;
	int			i;

	i = 0;
	result = (t_line **)malloc((unsigned long)ac * sizeof(t_line *));
	if (!result)
	{
		ft_putstr_fd("Error inr ft_get_line\n", 2);
		return (NULL);
	}
	result[ac - 1] = NULL;
	while (i < ac - 1)
	{
		if (i == 0)
			result[i] = ft_init_line(av[i + 1], 0, 1);
		else
			result[i] = ft_init_line(av[i + 1], 0, 0);
		i++;
	}
	return (result);
}
