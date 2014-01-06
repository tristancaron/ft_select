/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:24:19 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:24:19 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1 || !s2)
		return (s1);
	len = ft_strlen(s1);
	i = len;
	len += ft_strlen(s2);
	j = 0;
	while (i + j != len)
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}
