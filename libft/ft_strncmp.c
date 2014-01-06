/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:41:03 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:41:03 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((*s1 == *s2) && (*s1 != '\0' && *s2 != '\0') && (i != n - 1))
	{
		s1++;
		s2++;
		i++;
	}
	if (*s1 > *s2)
		return (1);
	else if (*s1 < *s2)
		return (-1);
	else
		return (0);
}
