/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:32:30 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 13:56:24 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void		ft_striter(char *s, void (*f)(char *))
{
	size_t	len;
	size_t	i;

	len = 0;
	if (!s || !f)
		return ;
	while (s[len] != '\0')
		len++;
	i = 0;
	while (i < len)
	{
		f(&s[i]);
		i++;
	}
	s[i] = '\0';
}
