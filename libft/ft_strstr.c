/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 11:01:00 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 11:01:01 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		len;

	len = (int)ft_strlen(s2);
	i = 0;
	if (len == 0 || !s1 || !s2)
		return ((char *) s1);
	while (s1[i] != '\0')
	{
		if (s1[i] == s2[0])
		{
			j = 0;
			while (s2[j] != '\0')
			{
				if (s2[j] != s1[i + j])
					break ;
				j++;
			}
			if (j == len)
				return ((char *) s1 + i);
		}
		i++;
	}
	return (NULL);
}
