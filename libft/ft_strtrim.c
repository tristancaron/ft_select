/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 11:18:25 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 11:18:26 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

unsigned int		ft_start(char const *s);
unsigned int		ft_end(char const *s);

char				*ft_strtrim(char const *s)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	alloc;
	int				i;
	char			*result;

	if (!s)
		return (NULL);
	start = ft_start(s);
	end = ft_end(s);
	alloc = (unsigned int)((ft_strlen(s)) - start - end);
	result = (char *)malloc(sizeof(char) * alloc);
	i = 0;
	while (start < end)
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}

unsigned int		ft_start(char const *s)
{
	unsigned int	start;

	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	return (start);
}

unsigned int		ft_end(char const *s)
{
	unsigned int	end;

	end = (unsigned int)(ft_strlen(s) - 1);
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	return (end + 1);
}
