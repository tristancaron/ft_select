/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:13:37 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:13:38 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

void		*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(n * sizeof(char));
	if (!tmp)
		return ((void *)0);
	while (i < n)
	{
		tmp[i] = ((char *)s2)[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		((char *)s1)[i] = tmp[i];
		i++;
	}
	free(tmp);
	return ((char *)s1);
}
