/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:52:19 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 13:33:09 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char		*ft_strnew(size_t size)
{
	char	*result;
	size_t	i;

	result = (char *)malloc(sizeof(char) * (size + 1));
	if (result)
	{
		i = 0;
		while (i <= size)
		{
			result[i] = '\0';
			i++;
		}
	}
	else
		return (NULL);
	return (result);
}
