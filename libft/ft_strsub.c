/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 11:14:12 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 11:14:13 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <stdlib.h>

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	leninit;
	size_t	i;
	char	*result;

	leninit = ft_strlen(s);
	if (leninit < len + start)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result)
	{
		i = 0;
		while (i != len)
		{
			result[i] = s[start + i];
			i++;
		}
		result[i] = '\0';
		return (result);
	}
	else
		return (NULL);
}
