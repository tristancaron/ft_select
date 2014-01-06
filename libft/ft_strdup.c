/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:31:28 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:31:28 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strdup(const char *s1)
{
	int		len;
	char	*res;
	int		i;

	if (!s1)
		return (NULL);
	len = (int)ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (res)
	{
		while (s1[i] != '\0')
		{
			res[i] = s1[i];
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	else
		return (NULL);
}
