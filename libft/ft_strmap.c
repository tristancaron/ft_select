/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:35:36 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:35:37 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len;
	size_t	i;
	char	*result;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len] != '\0')
		len++;
	result = (char *)malloc(sizeof(char) * len + 1);
	if (result)
	{
		i = 0;
		while (i != len)
		{
			result[i] = f(s[i]);
			i++;
		}
		result[i] = '\0';
		return (result);
	}
	else
		return (NULL);
}
