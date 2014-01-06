/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:33:05 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:33:05 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdlib.h>

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res)
	{
		i = 0;
		while (i != (ft_strlen(s1) + ft_strlen(s2)))
		{
			if (i < ft_strlen(s1))
				res[i] = s1[i];
			else
				res[i] = s2[i - ft_strlen(s1)];
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	else
		return (NULL);
}
