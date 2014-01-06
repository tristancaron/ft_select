/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:08:28 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:08:29 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void		*ft_memalloc(size_t size)
{
	void	*result;
	size_t	i;

	i = 0;
	result = (void *)malloc(size);
	if (!result)
		return (NULL);
	while (i < size)
	{
		((char *)result)[i] = '\0';
		i++;
	}
	return (result);
}
