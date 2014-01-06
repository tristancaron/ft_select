/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:54:23 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:54:24 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen(s2);
	i = 0;
	if (len == 0 || !s1 || !s2)
		return ((char *) s1);
	while (s1[i] != '\0')
	{
		if (s1[i] == s2[0])
		{
			j = 0;
			while (s2[j] != '\0' && j != n)
			{
				if (s2[j] != s1[i + j])
					break ;
				j++;
			}
			if (j == len && j <= n)
				return ((char *) s1 + i);
		}
		i++;
	}
	return ((char *) 0);
}
